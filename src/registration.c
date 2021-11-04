#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* FIXME: 
   Check these declarations against the C/Fortran source code.
*/

/* .C calls */
extern void sir_deterministic_rhs_dde(void *);
extern void sir_stochastic_rhs_dde(void *);

/* .Call calls */
extern SEXP sir_deterministic_contents(SEXP);
extern SEXP sir_deterministic_create(SEXP);
extern SEXP sir_deterministic_initial_conditions(SEXP, SEXP);
extern SEXP sir_deterministic_metadata(SEXP);
extern SEXP sir_deterministic_rhs_r(SEXP, SEXP, SEXP);
extern SEXP sir_deterministic_set_initial(SEXP, SEXP, SEXP, SEXP);
extern SEXP sir_deterministic_set_user(SEXP, SEXP);
extern SEXP sir_stochastic_contents(SEXP);
extern SEXP sir_stochastic_create(SEXP);
extern SEXP sir_stochastic_initial_conditions(SEXP, SEXP);
extern SEXP sir_stochastic_metadata(SEXP);
extern SEXP sir_stochastic_rhs_r(SEXP, SEXP, SEXP);
extern SEXP sir_stochastic_set_initial(SEXP, SEXP, SEXP, SEXP);
extern SEXP sir_stochastic_set_user(SEXP, SEXP);

static const R_CMethodDef CEntries[] = {
    {"sir_deterministic_rhs_dde", (DL_FUNC) &sir_deterministic_rhs_dde, 1},
    {"sir_stochastic_rhs_dde",    (DL_FUNC) &sir_stochastic_rhs_dde,    1},
    {NULL, NULL, 0}
};

static const R_CallMethodDef CallEntries[] = {
    {"sir_deterministic_contents",           (DL_FUNC) &sir_deterministic_contents,           1},
    {"sir_deterministic_create",             (DL_FUNC) &sir_deterministic_create,             1},
    {"sir_deterministic_initial_conditions", (DL_FUNC) &sir_deterministic_initial_conditions, 2},
    {"sir_deterministic_metadata",           (DL_FUNC) &sir_deterministic_metadata,           1},
    {"sir_deterministic_rhs_r",              (DL_FUNC) &sir_deterministic_rhs_r,              3},
    {"sir_deterministic_set_initial",        (DL_FUNC) &sir_deterministic_set_initial,        4},
    {"sir_deterministic_set_user",           (DL_FUNC) &sir_deterministic_set_user,           2},
    {"sir_stochastic_contents",              (DL_FUNC) &sir_stochastic_contents,              1},
    {"sir_stochastic_create",                (DL_FUNC) &sir_stochastic_create,                1},
    {"sir_stochastic_initial_conditions",    (DL_FUNC) &sir_stochastic_initial_conditions,    2},
    {"sir_stochastic_metadata",              (DL_FUNC) &sir_stochastic_metadata,              1},
    {"sir_stochastic_rhs_r",                 (DL_FUNC) &sir_stochastic_rhs_r,                 3},
    {"sir_stochastic_set_initial",           (DL_FUNC) &sir_stochastic_set_initial,           4},
    {"sir_stochastic_set_user",              (DL_FUNC) &sir_stochastic_set_user,              2},
    {NULL, NULL, 0}
};

void R_init_sir(DllInfo *dll)
{
    R_registerRoutines(dll, CEntries, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
