#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include <stdlib.h> // for NULL

// Compile with `-fvisibility=hidden -DHAVE_VISIBILITY_ATTRIBUTE` if you link to this library
#include <R_ext/Visibility.h>
#define export attribute_visible extern

extern SEXP c_my_fun(SEXP);
extern SEXP c_times_two_bad(SEXP);
extern SEXP c_times_two(SEXP);
extern SEXP c_times_two_no_protect(SEXP);

static const R_CallMethodDef CallEntries[] = {
  {"c_my_fun", (DL_FUNC) &c_my_fun, 1},
  {"c_times_two_bad", (DL_FUNC) &c_times_two_bad, 1},
  {"c_times_two", (DL_FUNC) &c_times_two, 1},
  {"c_times_two_no_protect", (DL_FUNC) &c_times_two_no_protect, 1},
  {NULL, NULL, 0}
};

export void R_init_cdemo(DllInfo *dll) {
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}
