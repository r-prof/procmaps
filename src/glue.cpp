extern "C" {
  extern void Rf_error(const char *str, ...);
}

void glue_abort() {
  Rf_error("Fatal error in gperftools");
}

#define glue_abort_msg Rf_error

#include "vendor/gperftools/src/base/sysinfo.cc"
#include "vendor/gperftools/src/base/logging.cc"

extern "C" {
  int FillProcSelfMaps(char buf[], int size, int* wrote_all) {
    bool wrote_all_b = false;
    int out = tcmalloc::FillProcSelfMaps(buf, size, &wrote_all_b);
    *wrote_all = wrote_all_b;
    return out;
  }
}
