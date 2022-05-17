#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>

SEXP c_my_fun(SEXP x) {
  Rprintf("about to print out x\n");
  Rf_PrintValue(x);
  Rprintf("done printing out x\n");
  return x;
}

SEXP c_times_two(SEXP x) {
  if (TYPEOF(x) != REALSXP) {
    Rf_error("`x` must be a double vector.");
  }

  R_xlen_t size = Rf_xlength(x);

  // Allocate double vector of size `size`.
  // Don't forget to protect it!
  SEXP out = PROTECT(Rf_allocVector(REALSXP, size));

  const double* v_x = REAL_RO(x);
  double* v_out = REAL(out);

  for (R_xlen_t i = 0; i < size; ++i) {
    v_out[i] = v_x[i] * 2;
  }

  UNPROTECT(1);
  return out;
}
