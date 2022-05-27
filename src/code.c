// These includes pull in the main parts of the C level R API
#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>

/*
 * Generally, most functions from this API are of the form:
 * `R_*()`
 * `Rf_*()`
 */

/*
 * Let's create a function that prints some strings out to the R console,
 * prints out our SEXP R object, and then returns it back to the user.
 *
 * Rprintf() - Like C's `printf()`, but reliably prints to the R console
 *
 * Rf_PrintValue() - Give it an R object and it will print it to the R console
 *
 * SEXP - Any R object. Yes, anything.
 */
SEXP c_my_fun(SEXP x) {
  Rprintf("about to print out x\n");
  Rf_PrintValue(x);
  Rprintf("done printing out x\n");
  return x;
}


/*
 * Here is another function that takes a double vector, times it by two,
 * and returns the result.
 *
 * Rf_xlength() - Get the length of an R object
 *
 * R_xlen_t - R's size type (like ssize_t)
 *
 * REAL(x) - If `x` is a double vector, please give me a pointer to the
 *           underlying C double array
 */
SEXP c_times_two_bad(SEXP x) {
  R_xlen_t size = Rf_xlength(x);

  double* v_x = REAL(x);

  for (R_xlen_t i = 0; i < size; ++i) {
    v_x[i] = v_x[i] * 2;
  }

  return x;
}

/*
 * Improved version that:
 * - Does some input checking
 * - Allocates a new vector rather than overwriting existing one
 *
 * TYPEOF() - Given an R object, what "type" is it? Returns an enum value.
 *
 * REALSXP - The enum value type corresponding to "double vector"
 *
 * Rf_allocVector(type, size) - Allocates memory for a C double array, then
 *  wraps it up inside a SEXP.
 *
 * PROTECT() - Protect the memory allocated by Rf_allocVector() to avoid it
 *  being automatically garbage collected by R. It you don't protect this,
 *  R will automatically free the memory the next time the gc runs, which
 *  you should generally assume happens somewhat randomly.
 *
 * REAL_RO() - Like `REAL()`, but returns a `const double*` rather than a
 *  `double*`. This keeps us from accidentally modifying `x`.
 *
 * UNPROTECT(n) - Unprotects the most recent `n` calls to `PROTECT()`.
 *  Since we are immediately returning this back to R, we are saying that we
 *  expect R itself to handle the protection of this object from now on.
 */
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

/*
 * This example doesn't protect `out`. How bad could that be?
 */
SEXP c_times_two_no_protect(SEXP x) {
  if (TYPEOF(x) != REALSXP) {
    Rf_error("`x` must be a double vector.");
  }

  R_xlen_t size = Rf_xlength(x);

  SEXP out = Rf_allocVector(REALSXP, size);
  double* v_out = REAL(out);

  // Allocate some other vector
  SEXP out2 = Rf_allocVector(REALSXP, 100000);
  REAL(out2)[0] = 1;

  R_gc();

  const double* v_x = REAL_RO(x);

  for (R_xlen_t i = 0; i < size; ++i) {
    v_out[i] = v_x[i] * 2;
  }

  return out;
}
