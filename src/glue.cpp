#define __STDC_FORMAT_MACROS
#include <inttypes.h>

extern "C" {
  extern void Rf_error(const char *str, ...);
}

void glue_abort() {
  Rf_error("Fatal error in gperftools");
}

#define glue_abort_msg Rf_error

#include "vendor/gperftools/src/base/sysinfo.cc"

extern "C" {
  typedef void (*populate_callback) (void *data, int row, int col, int total_rows, const char*);
  void PopulateProcSelfMapsDf(populate_callback cb, void* data) {
    ProcMapsIterator::Buffer iterbuf;

    int total_rows = 0;
    {
      ProcMapsIterator it(0, &iterbuf);   // 0 means "current pid"

      while (it.Next(NULL, NULL, NULL, NULL, NULL, NULL)) {
        ++total_rows;
      }
    }

    uint64 start, end, offset;
    int64 inode;
    char *flags, *filename;
    int row = 0;

    ProcMapsIterator it(0, &iterbuf);   // 0 means "current pid"
    while (it.Next(&start, &end, &flags, &offset, &inode, &filename)) {
      char buffer[17];

      snprintf(buffer, 17, "%016" PRIx64, start);
      cb(data, row, 0, total_rows, buffer);

      snprintf(buffer, 17, "%016" PRIx64, end);
      cb(data, row, 1, total_rows, buffer);

      // We assume 'flags' looks like 'rwxp' or 'rwx'.
      char r = (flags && flags[0] == 'r') ? 'r' : '-';
      char w = (flags && flags[0] && flags[1] == 'w') ? 'w' : '-';
      char x = (flags && flags[0] && flags[1] && flags[2] == 'x') ? 'x' : '-';
      // p always seems set on linux, so we set the default to 'p', not '-'
      char p = (flags && flags[0] && flags[1] && flags[2] && flags[3] != 'p')
        ? '-' : 'p';
      snprintf(buffer, sizeof(char) * 4 + 1, "%c%c%c%c", r, w, x, p);
      cb(data, row, 2, total_rows, buffer);

      snprintf(buffer, sizeof(uint64) + 1, "%08" PRIx64, offset);
      cb(data, row, 3, total_rows, buffer);

      snprintf(buffer, sizeof(int64) + 1, "%" PRId64, inode);
      cb(data, row, 4, total_rows, buffer);

      cb(data, row, 5, total_rows, filename);

      ++row;
    }
  }
}
