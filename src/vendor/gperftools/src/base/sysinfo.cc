// -*- Mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*-
// Copyright (c) 2006, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#if (defined(_WIN32) || defined(__MINGW32__)) && !defined(__CYGWIN__) && !defined(__CYGWIN32)
# define PLATFORM_WINDOWS 1
#endif

#include <ctype.h>    // for isspace()
#include <stdlib.h>   // for getenv()
#include <stdio.h>    // for snprintf(), sscanf()
#include <string.h>   // for memmove(), memchr(), etc.
#include <fcntl.h>    // for open()
#include <errno.h>    // for errno
#include <unistd.h>   // for read()
#if defined __MACH__          // Mac OS X, almost certainly
#include <mach-o/dyld.h>      // for iterating over dll's in ProcMapsIter
#include <mach-o/loader.h>    // for iterating over dll's in ProcMapsIter
#include <sys/types.h>
#include <sys/sysctl.h>       // how we figure out numcpu's on OS X
#elif defined __FreeBSD__
#include <sys/sysctl.h>
#elif defined __sun__         // Solaris
#include <procfs.h>           // for, e.g., prmap_t
#elif defined(PLATFORM_WINDOWS)
#include <process.h>          // for getpid() (actually, _getpid())
#include <shlwapi.h>          // for SHGetValueA()
#include <tlhelp32.h>         // for Module32First()
#endif
#include "base/sysinfo.h"

#ifdef PLATFORM_WINDOWS
#ifdef MODULEENTRY32
// In a change from the usual W-A pattern, there is no A variant of
// MODULEENTRY32.  Tlhelp32.h #defines the W variant, but not the A.
// In unicode mode, tlhelp32.h #defines MODULEENTRY32 to be
// MODULEENTRY32W.  These #undefs are the only way I see to get back
// access to the original, ascii struct (and related functions).
#undef MODULEENTRY32
#undef Module32First
#undef Module32Next
#undef PMODULEENTRY32
#undef LPMODULEENTRY32
#endif  /* MODULEENTRY32 */
// MinGW doesn't seem to define this, perhaps some windowsen don't either.
#ifndef TH32CS_SNAPMODULE32
#define TH32CS_SNAPMODULE32  0
#endif  /* TH32CS_SNAPMODULE32 */
#endif  /* PLATFORM_WINDOWS */

// Re-run fn until it doesn't cause EINTR.
#define NO_INTR(fn)  do {} while ((fn) < 0 && errno == EINTR)



// ----------------------------------------------------------------------

#if defined __linux__ || defined __FreeBSD__ || defined __sun__ || defined __CYGWIN__ || defined __CYGWIN32__
static void ConstructFilename(const char* spec, pid_t pid,
                              char* buf, int buf_size) {
  CHECK_LT(snprintf(buf, buf_size,
                    spec,
                    static_cast<int>(pid ? pid : getpid())), buf_size);
}
#endif

// A templatized helper function instantiated for Mach (OS X) only.
// It can handle finding info for both 32 bits and 64 bits.
// Returns true if it successfully handled the hdr, false else.
#ifdef __MACH__          // Mac OS X, almost certainly
template<uint32_t kMagic, uint32_t kLCSegment,
         typename MachHeader, typename SegmentCommand>
static bool NextExtMachHelper(const mach_header* hdr,
                              int current_image, int current_load_cmd,
                              uint64 *start, uint64 *end, char **flags,
                              uint64 *offset, int64 *inode, char **filename) {
  static char kDefaultPerms[5] = "r-xp";
  if (hdr->magic != kMagic)
    return false;
  const char* lc = (const char *)hdr + sizeof(MachHeader);
  // TODO(csilvers): make this not-quadradic (increment and hold state)
  for (int j = 0; j < current_load_cmd; j++)  // advance to *our* load_cmd
    lc += ((const load_command *)lc)->cmdsize;
  if (((const load_command *)lc)->cmd == kLCSegment) {
    const intptr_t dlloff = _dyld_get_image_vmaddr_slide(current_image);
    const SegmentCommand* sc = (const SegmentCommand *)lc;
    if (start) *start = sc->vmaddr + dlloff;
    if (end) *end = sc->vmaddr + sc->vmsize + dlloff;
    if (flags) *flags = kDefaultPerms;  // can we do better?
    if (offset) *offset = sc->fileoff;
    if (inode) *inode = 0;
    if (filename)
      *filename = const_cast<char*>(_dyld_get_image_name(current_image));
    return true;
  }

  return false;
}
#endif

#if defined(__linux__)
// Finds |c| in |text|, and assign '\0' at the found position.
// The original character at the modified position should be |c|.
// A pointer to the modified position is stored in |endptr|.
// |endptr| should not be NULL.
static bool ExtractUntilChar(char *text, int c, char **endptr) {
  CHECK_NE(text, NULL);
  CHECK_NE(endptr, NULL);
  char *found;
  found = strchr(text, c);
  if (found == NULL) {
    *endptr = NULL;
    return false;
  }

  *endptr = found;
  *found = '\0';
  return true;
}

// Increments |*text_pointer| while it points a whitespace character.
// It is to follow sscanf's whilespace handling.
static void SkipWhileWhitespace(char **text_pointer, int c) {
  if (isspace(c)) {
    while (isspace(**text_pointer) && isspace(*((*text_pointer) + 1))) {
      ++(*text_pointer);
    }
  }
}

template<class T>
static T StringToInteger(char *text, char **endptr, int base) {
  assert(false);
  return T();
}

template<>
int StringToInteger<int>(char *text, char **endptr, int base) {
  return strtol(text, endptr, base);
}

template<>
int64 StringToInteger<int64>(char *text, char **endptr, int base) {
  return strtoll(text, endptr, base);
}

template<>
uint64 StringToInteger<uint64>(char *text, char **endptr, int base) {
  return strtoull(text, endptr, base);
}

template<typename T>
static T StringToIntegerUntilChar(
    char *text, int base, int c, char **endptr_result) {
  CHECK_NE(endptr_result, NULL);
  *endptr_result = NULL;

  char *endptr_extract;
  if (!ExtractUntilChar(text, c, &endptr_extract))
    return 0;

  T result;
  char *endptr_strto;
  result = StringToInteger<T>(text, &endptr_strto, base);
  *endptr_extract = c;

  if (endptr_extract != endptr_strto)
    return 0;

  *endptr_result = endptr_extract;
  SkipWhileWhitespace(endptr_result, c);

  return result;
}

static char *CopyStringUntilChar(
    char *text, unsigned out_len, int c, char *out) {
  char *endptr;
  if (!ExtractUntilChar(text, c, &endptr))
    return NULL;

  strncpy(out, text, out_len);
  out[out_len-1] = '\0';
  *endptr = c;

  SkipWhileWhitespace(&endptr, c);
  return endptr;
}

template<typename T>
static bool StringToIntegerUntilCharWithCheck(
    T *outptr, char *text, int base, int c, char **endptr) {
  *outptr = StringToIntegerUntilChar<T>(*endptr, base, c, endptr);
  if (*endptr == NULL || **endptr == '\0') return false;
  ++(*endptr);
  return true;
}

static bool ParseProcMapsLine(char *text, uint64 *start, uint64 *end,
                              char *flags, uint64 *offset,
                              int *major, int *minor, int64 *inode,
                              unsigned *filename_offset) {
  /*
   * It's similar to:
   * sscanf(text, "%"SCNx64"-%"SCNx64" %4s %"SCNx64" %x:%x %"SCNd64" %n",
   *        start, end, flags, offset, major, minor, inode, filename_offset)
   */
  char *endptr = text;
  if (endptr == NULL || *endptr == '\0')  return false;

  if (!StringToIntegerUntilCharWithCheck(start, endptr, 16, '-', &endptr))
    return false;

  if (!StringToIntegerUntilCharWithCheck(end, endptr, 16, ' ', &endptr))
    return false;

  endptr = CopyStringUntilChar(endptr, 5, ' ', flags);
  if (endptr == NULL || *endptr == '\0')  return false;
  ++endptr;

  if (!StringToIntegerUntilCharWithCheck(offset, endptr, 16, ' ', &endptr))
    return false;

  if (!StringToIntegerUntilCharWithCheck(major, endptr, 16, ':', &endptr))
    return false;

  if (!StringToIntegerUntilCharWithCheck(minor, endptr, 16, ' ', &endptr))
    return false;

  if (!StringToIntegerUntilCharWithCheck(inode, endptr, 10, ' ', &endptr))
    return false;

  *filename_offset = (endptr - text);
  return true;
}
#endif

ProcMapsIterator::ProcMapsIterator(pid_t pid) {
  Init(pid, NULL, false);
}

ProcMapsIterator::ProcMapsIterator(pid_t pid, Buffer *buffer) {
  Init(pid, buffer, false);
}

ProcMapsIterator::ProcMapsIterator(pid_t pid, Buffer *buffer,
                                   bool use_maps_backing) {
  Init(pid, buffer, use_maps_backing);
}

void ProcMapsIterator::Init(pid_t pid, Buffer *buffer,
                            bool use_maps_backing) {
  pid_ = pid;
  using_maps_backing_ = use_maps_backing;
  dynamic_buffer_ = NULL;
  if (!buffer) {
    // If the user didn't pass in any buffer storage, allocate it
    // now. This is the normal case; the signal handler passes in a
    // static buffer.
    buffer = dynamic_buffer_ = new Buffer;
  } else {
    dynamic_buffer_ = NULL;
  }

  ibuf_ = buffer->buf_;

  stext_ = etext_ = nextline_ = ibuf_;
  ebuf_ = ibuf_ + Buffer::kBufSize - 1;
  nextline_ = ibuf_;

#if defined(__linux__) || defined(__CYGWIN__) || defined(__CYGWIN32__)
  if (use_maps_backing) {  // don't bother with clever "self" stuff in this case
    ConstructFilename("/proc/%d/maps_backing", pid, ibuf_, Buffer::kBufSize);
  } else if (pid == 0) {
    // We have to kludge a bit to deal with the args ConstructFilename
    // expects.  The 1 is never used -- it's only impt. that it's not 0.
    ConstructFilename("/proc/self/maps", 1, ibuf_, Buffer::kBufSize);
  } else {
    ConstructFilename("/proc/%d/maps", pid, ibuf_, Buffer::kBufSize);
  }
  // No error logging since this can be called from the crash dump
  // handler at awkward moments. Users should call Valid() before
  // using.
  NO_INTR(fd_ = open(ibuf_, O_RDONLY));
#elif defined(__FreeBSD__)
  // We don't support maps_backing on freebsd
  if (pid == 0) {
    ConstructFilename("/proc/curproc/map", 1, ibuf_, Buffer::kBufSize);
  } else {
    ConstructFilename("/proc/%d/map", pid, ibuf_, Buffer::kBufSize);
  }
  NO_INTR(fd_ = open(ibuf_, O_RDONLY));
#elif defined(__sun__)
  if (pid == 0) {
    ConstructFilename("/proc/self/map", 1, ibuf_, Buffer::kBufSize);
  } else {
    ConstructFilename("/proc/%d/map", pid, ibuf_, Buffer::kBufSize);
  }
  NO_INTR(fd_ = open(ibuf_, O_RDONLY));
#elif defined(__MACH__)
  current_image_ = _dyld_image_count();   // count down from the top
  current_load_cmd_ = -1;
#elif defined(PLATFORM_WINDOWS)
  snapshot_ = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE |
                                       TH32CS_SNAPMODULE32,
                                       GetCurrentProcessId());
  memset(&module_, 0, sizeof(module_));
#else
  fd_ = -1;   // so Valid() is always false
#endif

}

ProcMapsIterator::~ProcMapsIterator() {
#if defined(PLATFORM_WINDOWS)
  if (snapshot_ != INVALID_HANDLE_VALUE) CloseHandle(snapshot_);
#elif defined(__MACH__)
  // no cleanup necessary!
#else
  if (fd_ >= 0) NO_INTR(close(fd_));
#endif
  delete dynamic_buffer_;
}

bool ProcMapsIterator::Valid() const {
#if defined(PLATFORM_WINDOWS)
  return snapshot_ != INVALID_HANDLE_VALUE;
#elif defined(__MACH__)
  return 1;
#else
  return fd_ != -1;
#endif
}

bool ProcMapsIterator::Next(uint64 *start, uint64 *end, char **flags,
                            uint64 *offset, int64 *inode, char **filename) {

#if defined(__linux__) || defined(__FreeBSD__) || defined(__CYGWIN__) || defined(__CYGWIN32__)
  do {
    // Advance to the start of the next line
    stext_ = nextline_;

    // See if we have a complete line in the buffer already
    nextline_ = static_cast<char *>(memchr (stext_, '\n', etext_ - stext_));
    if (!nextline_) {
      // Shift/fill the buffer so we do have a line
      int count = etext_ - stext_;

      // Move the current text to the start of the buffer
      memmove(ibuf_, stext_, count);
      stext_ = ibuf_;
      etext_ = ibuf_ + count;

      int nread = 0;            // fill up buffer with text
      while (etext_ < ebuf_) {
        NO_INTR(nread = read(fd_, etext_, ebuf_ - etext_));
        if (nread > 0)
          etext_ += nread;
        else
          break;
      }

      // Zero out remaining characters in buffer at EOF to avoid returning
      // garbage from subsequent calls.
      if (etext_ != ebuf_ && nread == 0) {
        memset(etext_, 0, ebuf_ - etext_);
      }
      *etext_ = '\n';   // sentinel; safe because ibuf extends 1 char beyond ebuf
      nextline_ = static_cast<char *>(memchr (stext_, '\n', etext_ + 1 - stext_));
    }
    *nextline_ = 0;                // turn newline into nul
    nextline_ += ((nextline_ < etext_)? 1 : 0);  // skip nul if not end of text
    // stext_ now points at a nul-terminated line
    uint64 tmpstart, tmpend, tmpoffset;
    int64 tmpinode;
    int major, minor;
    unsigned filename_offset = 0;
#if defined(__linux__)
    // for now, assume all linuxes have the same format
    if (!ParseProcMapsLine(
        stext_,
        start ? start : &tmpstart,
        end ? end : &tmpend,
        flags_,
        offset ? offset : &tmpoffset,
        &major, &minor,
        inode ? inode : &tmpinode, &filename_offset)) continue;
#elif defined(__CYGWIN__) || defined(__CYGWIN32__)
    // cygwin is like linux, except the third field is the "entry point"
    // rather than the offset (see format_process_maps at
    // http://cygwin.com/cgi-bin/cvsweb.cgi/src/winsup/cygwin/fhandler_process.cc?rev=1.89&content-type=text/x-cvsweb-markup&cvsroot=src
    // Offset is always be 0 on cygwin: cygwin implements an mmap
    // by loading the whole file and then calling NtMapViewOfSection.
    // Cygwin also seems to set its flags kinda randomly; use windows default.
    char tmpflags[5];
    if (offset)
      *offset = 0;
    strcpy(flags_, "r-xp");
    if (sscanf(stext_, "%llx-%llx %4s %llx %x:%x %lld %n",
               start ? start : &tmpstart,
               end ? end : &tmpend,
               tmpflags,
               &tmpoffset,
               &major, &minor,
               inode ? inode : &tmpinode, &filename_offset) != 7) continue;
#elif defined(__FreeBSD__)
    // For the format, see http://www.freebsd.org/cgi/cvsweb.cgi/src/sys/fs/procfs/procfs_map.c?rev=1.31&content-type=text/x-cvsweb-markup
    tmpstart = tmpend = tmpoffset = 0;
    tmpinode = 0;
    major = minor = 0;   // can't get this info in freebsd
    if (inode)
      *inode = 0;        // nor this
    if (offset)
      *offset = 0;       // seems like this should be in there, but maybe not
    // start end resident privateresident obj(?) prot refcnt shadowcnt
    // flags copy_on_write needs_copy type filename:
    // 0x8048000 0x804a000 2 0 0xc104ce70 r-x 1 0 0x0 COW NC vnode /bin/cat
    if (sscanf(stext_, "0x%" SCNx64 " 0x%" SCNx64 " %*d %*d %*p %3s %*d %*d 0x%*x %*s %*s %*s %n",
               start ? start : &tmpstart,
               end ? end : &tmpend,
               flags_,
               &filename_offset) != 3) continue;
#endif

    // Depending on the Linux kernel being used, there may or may not be a space
    // after the inode if there is no filename.  sscanf will in such situations
    // nondeterministically either fill in filename_offset or not (the results
    // differ on multiple calls in the same run even with identical arguments).
    // We don't want to wander off somewhere beyond the end of the string.
    size_t stext_length = strlen(stext_);
    if (filename_offset == 0 || filename_offset > stext_length)
      filename_offset = stext_length;

    // We found an entry
    if (flags) *flags = flags_;
    if (filename) *filename = stext_ + filename_offset;

    return true;
  } while (etext_ > ibuf_);
#elif defined(__sun__)
  // Translation to MA_READ == 4, MA_WRITE == 2, MA_EXEC == 1 is done separately
  static char kPerms[8][4] = { "---", "--x", "-w-", "-wx",
                               "r--", "r-x", "rw-", "rwx" };
  Buffer object_path;
  int nread = 0;            // fill up buffer with text
  NO_INTR(nread = read(fd_, ibuf_, sizeof(prmap_t)));
  if (nread == sizeof(prmap_t)) {
    long inode_from_mapname = 0;
    prmap_t* mapinfo = reinterpret_cast<prmap_t*>(ibuf_);
    // Best-effort attempt to get the inode from the filename.  I think the
    // two middle ints are major and minor device numbers, but I'm not sure.
    sscanf(mapinfo->pr_mapname, "ufs.%*d.%*d.%ld", &inode_from_mapname);

    if (pid_ == 0) {
      CHECK_LT(snprintf(object_path.buf_, Buffer::kBufSize,
                        "/proc/self/path/%s", mapinfo->pr_mapname),
               Buffer::kBufSize);
    } else {
      CHECK_LT(snprintf(object_path.buf_, Buffer::kBufSize,
                        "/proc/%d/path/%s",
                        static_cast<int>(pid_), mapinfo->pr_mapname),
               Buffer::kBufSize);
    }
    ssize_t len = readlink(object_path.buf_, current_filename_, PATH_MAX);
    CHECK_LT(len, PATH_MAX);
    if (len < 0)
      len = 0;
    current_filename_[len] = '\0';

    if (start) *start = mapinfo->pr_vaddr;
    if (end) *end = mapinfo->pr_vaddr + mapinfo->pr_size;
    if (flags) {
      int mflags =
        (mapinfo->pr_mflags & MA_READ) ? 4 : 0 |
        (mapinfo->pr_mflags & MA_WRITE) ? 2 : 0 |
        (mapinfo->pr_mflags & MA_EXEC) ? 1 : 0;

      *flags = kPerms[mflags];
    }
    if (offset) *offset = mapinfo->pr_offset;
    if (inode) *inode = inode_from_mapname;
    if (filename) *filename = current_filename_;
    return true;
  }
#elif defined(__MACH__)
  // We return a separate entry for each segment in the DLL. (TODO(csilvers):
  // can we do better?)  A DLL ("image") has load-commands, some of which
  // talk about segment boundaries.
  // cf image_for_address from http://svn.digium.com/view/asterisk/team/oej/minivoicemail/dlfcn.c?revision=53912
  for (; current_image_ >= 0; current_image_--) {
    const mach_header* hdr = _dyld_get_image_header(current_image_);
    if (!hdr) continue;
    if (current_load_cmd_ < 0)   // set up for this image
      current_load_cmd_ = hdr->ncmds;  // again, go from the top down

    // We start with the next load command (we've already looked at this one).
    for (current_load_cmd_--; current_load_cmd_ >= 0; current_load_cmd_--) {
#ifdef MH_MAGIC_64
      if (NextExtMachHelper<MH_MAGIC_64, LC_SEGMENT_64,
                            struct mach_header_64, struct segment_command_64>(
                                hdr, current_image_, current_load_cmd_,
                                start, end, flags, offset, inode, filename)) {
        return true;
      }
#endif
      if (NextExtMachHelper<MH_MAGIC, LC_SEGMENT,
                            struct mach_header, struct segment_command>(
                                hdr, current_image_, current_load_cmd_,
                                start, end, flags, offset, inode, filename)) {
        return true;
      }
    }
    // If we get here, no more load_cmd's in this image talk about
    // segments.  Go on to the next image.
  }
#elif defined(PLATFORM_WINDOWS)
  static char kDefaultPerms[5] = "r-xp";
  BOOL ok;
  if (module_.dwSize == 0) {  // only possible before first call
    module_.dwSize = sizeof(module_);
    ok = Module32First(snapshot_, &module_);
  } else {
    ok = Module32Next(snapshot_, &module_);
  }
  if (ok) {
    uint64 base_addr = reinterpret_cast<DWORD_PTR>(module_.modBaseAddr);
    if (start) *start = base_addr;
    if (end) *end = base_addr + module_.modBaseSize;
    if (flags) *flags = kDefaultPerms;
    if (offset) *offset = 0;
    if (inode) *inode = 0;
    if (filename) *filename = module_.szExePath;
    return true;
  }
#endif

  // We didn't find anything
  return false;
}
