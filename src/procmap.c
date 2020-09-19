#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>

typedef void (*populate_callback) (void *data, int row, int col, int total_rows, const char*);
void PopulateProcSelfMapsDf(populate_callback cb, void* data);

void populate_callback_df(void *data, int row, int col, int total_rows, const char* value) {
  SEXP df = (SEXP)data;

  SEXP col_data = VECTOR_ELT(df, col);
  if (col_data == R_NilValue) {
    col_data = Rf_allocVector(STRSXP, (R_xlen_t)total_rows);
    SET_VECTOR_ELT(df, col, col_data);
  }

  SET_STRING_ELT(col_data, row, Rf_mkChar(value));
}

SEXP procmaps_procmap_get_df() {
  SEXP out = PROTECT(Rf_allocVector(VECSXP, 6));
  PopulateProcSelfMapsDf(populate_callback_df, (void*)out);
  UNPROTECT(1);
  return out;
}
