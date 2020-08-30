#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>

#include "vendor/gperftools/src/base/logging.cc"
#include "vendor/gperftools/src/base/sysinfo.cc"

extern "C" {
  int FillProcSelfMaps(char buf[], int size, int* wrote_all) {
    bool wrote_all_b = false;
    int out = tcmalloc::FillProcSelfMaps(buf, size, &wrote_all_b);
    *wrote_all = wrote_all_b;
    return out;
  }
}
