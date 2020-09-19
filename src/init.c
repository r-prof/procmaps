#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>

// Compile with `-fvisibility=hidden -DHAVE_VISIBILITY_ATTRIBUTE` if you link to this library
#include <R_ext/Visibility.h>
#define export attribute_visible extern

extern SEXP procmaps_procmap_get();
extern SEXP procmaps_procmap_get_df();

static const R_CallMethodDef CallEntries[] = {
  {"procmaps_c_procmap_get",                 (DL_FUNC) &procmaps_procmap_get, 0},
  {"procmaps_c_procmap_get_df",              (DL_FUNC) &procmaps_procmap_get_df, 0},

  {NULL, NULL, 0}
};

export void R_init_procmaps(DllInfo *dll)
{
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}
