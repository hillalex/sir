// Automatically generated by odin 1.2.1 - do not edit
#include <R.h>
#include <Rmath.h>
#include <Rinternals.h>
#include <stdbool.h>
#include <R_ext/Rdynload.h>
typedef struct sir_deterministic_internal {
  double beta;
  double I_ini;
  double initial_I;
  double initial_R;
  double initial_S;
  double S_ini;
  double sigma;
} sir_deterministic_internal;
typedef struct sir_stochastic_internal {
  double beta;
  int dim_I;
  int dim_N;
  int dim_n_IR;
  int dim_n_SI;
  int dim_p_SI;
  int dim_R;
  int dim_S;
  double I_ini;
  double *initial_I;
  double *initial_R;
  double *initial_S;
  double *N;
  double *n_IR;
  double *n_SI;
  int nsim;
  int offset_variable_R;
  double p_IR;
  double *p_SI;
  double S_ini;
  double sigma;
} sir_stochastic_internal;
sir_deterministic_internal* sir_deterministic_get_internal(SEXP internal_p, int closed_error);
static void sir_deterministic_finalise(SEXP internal_p);
SEXP sir_deterministic_create(SEXP user);
void sir_deterministic_initmod_desolve(void(* odeparms) (int *, double *));
SEXP sir_deterministic_contents(SEXP internal_p);
SEXP sir_deterministic_set_user(SEXP internal_p, SEXP user);
SEXP sir_deterministic_set_initial(SEXP internal_p, SEXP step_ptr, SEXP state_ptr);
SEXP sir_deterministic_metadata(SEXP internal_p);
SEXP sir_deterministic_initial_conditions(SEXP internal_p, SEXP step_ptr);
void sir_deterministic_rhs(sir_deterministic_internal* internal, size_t step, double * state, double * state_next, double * output);
void sir_deterministic_rhs_dde(size_t n_eq, size_t step, double * state, double * state_next, size_t n_out, double * output, void * internal);
SEXP sir_deterministic_rhs_r(SEXP internal_p, SEXP step, SEXP state);
sir_stochastic_internal* sir_stochastic_get_internal(SEXP internal_p, int closed_error);
static void sir_stochastic_finalise(SEXP internal_p);
SEXP sir_stochastic_create(SEXP user);
void sir_stochastic_initmod_desolve(void(* odeparms) (int *, double *));
SEXP sir_stochastic_contents(SEXP internal_p);
SEXP sir_stochastic_set_user(SEXP internal_p, SEXP user);
SEXP sir_stochastic_set_initial(SEXP internal_p, SEXP step_ptr, SEXP state_ptr);
SEXP sir_stochastic_metadata(SEXP internal_p);
SEXP sir_stochastic_initial_conditions(SEXP internal_p, SEXP step_ptr);
void sir_stochastic_rhs(sir_stochastic_internal* internal, size_t step, double * state, double * state_next, double * output);
void sir_stochastic_rhs_dde(size_t n_eq, size_t step, double * state, double * state_next, size_t n_out, double * output, void * internal);
SEXP sir_stochastic_rhs_r(SEXP internal_p, SEXP step, SEXP state);
double user_get_scalar_double(SEXP user, const char *name,
                              double default_value, double min, double max);
int user_get_scalar_int(SEXP user, const char *name,
                        int default_value, double min, double max);
void user_check_values_double(double * value, size_t len,
                                  double min, double max, const char *name);
void user_check_values_int(int * value, size_t len,
                               double min, double max, const char *name);
void user_check_values(SEXP value, double min, double max,
                           const char *name);
SEXP user_list_element(SEXP list, const char *name);
int scalar_int(SEXP x, const char * name);
sir_deterministic_internal* sir_deterministic_get_internal(SEXP internal_p, int closed_error) {
  sir_deterministic_internal *internal = NULL;
  if (TYPEOF(internal_p) != EXTPTRSXP) {
    Rf_error("Expected an external pointer");
  }
  internal = (sir_deterministic_internal*) R_ExternalPtrAddr(internal_p);
  if (!internal && closed_error) {
    Rf_error("Pointer has been invalidated");
  }
  return internal;
}
void sir_deterministic_finalise(SEXP internal_p) {
  sir_deterministic_internal *internal = sir_deterministic_get_internal(internal_p, 0);
  if (internal_p) {
    Free(internal);
    R_ClearExternalPtr(internal_p);
  }
}
SEXP sir_deterministic_create(SEXP user) {
  sir_deterministic_internal *internal = (sir_deterministic_internal*) Calloc(1, sir_deterministic_internal);
  internal->initial_R = 0;
  internal->beta = NA_REAL;
  internal->I_ini = NA_REAL;
  internal->S_ini = NA_REAL;
  internal->sigma = NA_REAL;
  SEXP ptr = PROTECT(R_MakeExternalPtr(internal, R_NilValue, R_NilValue));
  R_RegisterCFinalizer(ptr, sir_deterministic_finalise);
  UNPROTECT(1);
  return ptr;
}
static sir_deterministic_internal *sir_deterministic_internal_ds;
void sir_deterministic_initmod_desolve(void(* odeparms) (int *, double *)) {
  static DL_FUNC get_desolve_gparms = NULL;
  if (get_desolve_gparms == NULL) {
    get_desolve_gparms =
      R_GetCCallable("deSolve", "get_deSolve_gparms");
  }
  sir_deterministic_internal_ds = sir_deterministic_get_internal(get_desolve_gparms(), 1);
}
SEXP sir_deterministic_contents(SEXP internal_p) {
  sir_deterministic_internal *internal = sir_deterministic_get_internal(internal_p, 1);
  SEXP contents = PROTECT(allocVector(VECSXP, 7));
  SET_VECTOR_ELT(contents, 0, ScalarReal(internal->beta));
  SET_VECTOR_ELT(contents, 1, ScalarReal(internal->I_ini));
  SET_VECTOR_ELT(contents, 2, ScalarReal(internal->initial_I));
  SET_VECTOR_ELT(contents, 3, ScalarReal(internal->initial_R));
  SET_VECTOR_ELT(contents, 4, ScalarReal(internal->initial_S));
  SET_VECTOR_ELT(contents, 5, ScalarReal(internal->S_ini));
  SET_VECTOR_ELT(contents, 6, ScalarReal(internal->sigma));
  SEXP nms = PROTECT(allocVector(STRSXP, 7));
  SET_STRING_ELT(nms, 0, mkChar("beta"));
  SET_STRING_ELT(nms, 1, mkChar("I_ini"));
  SET_STRING_ELT(nms, 2, mkChar("initial_I"));
  SET_STRING_ELT(nms, 3, mkChar("initial_R"));
  SET_STRING_ELT(nms, 4, mkChar("initial_S"));
  SET_STRING_ELT(nms, 5, mkChar("S_ini"));
  SET_STRING_ELT(nms, 6, mkChar("sigma"));
  setAttrib(contents, R_NamesSymbol, nms);
  UNPROTECT(2);
  return contents;
}
SEXP sir_deterministic_set_user(SEXP internal_p, SEXP user) {
  sir_deterministic_internal *internal = sir_deterministic_get_internal(internal_p, 1);
  internal->beta = user_get_scalar_double(user, "beta", internal->beta, NA_REAL, NA_REAL);
  internal->I_ini = user_get_scalar_double(user, "I_ini", internal->I_ini, NA_REAL, NA_REAL);
  internal->S_ini = user_get_scalar_double(user, "S_ini", internal->S_ini, NA_REAL, NA_REAL);
  internal->sigma = user_get_scalar_double(user, "sigma", internal->sigma, NA_REAL, NA_REAL);
  internal->initial_I = internal->I_ini;
  internal->initial_S = internal->S_ini;
  return R_NilValue;
}
SEXP sir_deterministic_set_initial(SEXP internal_p, SEXP step_ptr, SEXP state_ptr) {
  return R_NilValue;
}
SEXP sir_deterministic_metadata(SEXP internal_p) {
  sir_deterministic_internal *internal = sir_deterministic_get_internal(internal_p, 1);
  SEXP ret = PROTECT(allocVector(VECSXP, 4));
  SEXP nms = PROTECT(allocVector(STRSXP, 4));
  SET_STRING_ELT(nms, 0, mkChar("variable_order"));
  SET_STRING_ELT(nms, 1, mkChar("output_order"));
  SET_STRING_ELT(nms, 2, mkChar("n_out"));
  SET_STRING_ELT(nms, 3, mkChar("interpolate_t"));
  setAttrib(ret, R_NamesSymbol, nms);
  SEXP variable_length = PROTECT(allocVector(VECSXP, 3));
  SEXP variable_names = PROTECT(allocVector(STRSXP, 3));
  setAttrib(variable_length, R_NamesSymbol, variable_names);
  SET_VECTOR_ELT(variable_length, 0, R_NilValue);
  SET_VECTOR_ELT(variable_length, 1, R_NilValue);
  SET_VECTOR_ELT(variable_length, 2, R_NilValue);
  SET_STRING_ELT(variable_names, 0, mkChar("S"));
  SET_STRING_ELT(variable_names, 1, mkChar("I"));
  SET_STRING_ELT(variable_names, 2, mkChar("R"));
  SET_VECTOR_ELT(ret, 0, variable_length);
  UNPROTECT(2);
  SET_VECTOR_ELT(ret, 1, R_NilValue);
  SET_VECTOR_ELT(ret, 2, ScalarInteger(0));
  UNPROTECT(2);
  return ret;
}
SEXP sir_deterministic_initial_conditions(SEXP internal_p, SEXP step_ptr) {
  sir_deterministic_internal *internal = sir_deterministic_get_internal(internal_p, 1);
  SEXP r_state = PROTECT(allocVector(REALSXP, 3));
  double * state = REAL(r_state);
  state[0] = internal->initial_S;
  state[1] = internal->initial_I;
  state[2] = internal->initial_R;
  UNPROTECT(1);
  return r_state;
}
void sir_deterministic_rhs(sir_deterministic_internal* internal, size_t step, double * state, double * state_next, double * output) {
  double S = state[0];
  double I = state[1];
  double R = state[2];
  double N = S + I + R;
  state_next[2] = R + internal->sigma * I;
  state_next[1] = I + internal->beta * S * I / (double) N - internal->sigma * I;
  state_next[0] = S - internal->beta * S * I / (double) N;
}
void sir_deterministic_rhs_dde(size_t n_eq, size_t step, double * state, double * state_next, size_t n_out, double * output, void * internal) {
  sir_deterministic_rhs((sir_deterministic_internal*)internal, step, state, state_next, output);
}
SEXP sir_deterministic_rhs_r(SEXP internal_p, SEXP step, SEXP state) {
  SEXP state_next = PROTECT(allocVector(REALSXP, LENGTH(state)));
  sir_deterministic_internal *internal = sir_deterministic_get_internal(internal_p, 1);
  double *output = NULL;
  sir_deterministic_rhs(internal, scalar_int(step, "step"), REAL(state), REAL(state_next), output);
  UNPROTECT(1);
  return state_next;
}
sir_stochastic_internal* sir_stochastic_get_internal(SEXP internal_p, int closed_error) {
  sir_stochastic_internal *internal = NULL;
  if (TYPEOF(internal_p) != EXTPTRSXP) {
    Rf_error("Expected an external pointer");
  }
  internal = (sir_stochastic_internal*) R_ExternalPtrAddr(internal_p);
  if (!internal && closed_error) {
    Rf_error("Pointer has been invalidated");
  }
  return internal;
}
void sir_stochastic_finalise(SEXP internal_p) {
  sir_stochastic_internal *internal = sir_stochastic_get_internal(internal_p, 0);
  if (internal_p) {
    Free(internal->initial_I);
    Free(internal->initial_R);
    Free(internal->initial_S);
    Free(internal->N);
    Free(internal->n_IR);
    Free(internal->n_SI);
    Free(internal->p_SI);
    Free(internal);
    R_ClearExternalPtr(internal_p);
  }
}
SEXP sir_stochastic_create(SEXP user) {
  sir_stochastic_internal *internal = (sir_stochastic_internal*) Calloc(1, sir_stochastic_internal);
  internal->initial_I = NULL;
  internal->initial_R = NULL;
  internal->initial_S = NULL;
  internal->N = NULL;
  internal->n_IR = NULL;
  internal->n_SI = NULL;
  internal->p_SI = NULL;
  internal->beta = NA_REAL;
  internal->I_ini = NA_REAL;
  internal->nsim = NA_INTEGER;
  internal->S_ini = NA_REAL;
  internal->sigma = NA_REAL;
  SEXP ptr = PROTECT(R_MakeExternalPtr(internal, R_NilValue, R_NilValue));
  R_RegisterCFinalizer(ptr, sir_stochastic_finalise);
  UNPROTECT(1);
  return ptr;
}
static sir_stochastic_internal *sir_stochastic_internal_ds;
void sir_stochastic_initmod_desolve(void(* odeparms) (int *, double *)) {
  static DL_FUNC get_desolve_gparms = NULL;
  if (get_desolve_gparms == NULL) {
    get_desolve_gparms =
      R_GetCCallable("deSolve", "get_deSolve_gparms");
  }
  sir_stochastic_internal_ds = sir_stochastic_get_internal(get_desolve_gparms(), 1);
}
SEXP sir_stochastic_contents(SEXP internal_p) {
  sir_stochastic_internal *internal = sir_stochastic_get_internal(internal_p, 1);
  SEXP contents = PROTECT(allocVector(VECSXP, 21));
  SET_VECTOR_ELT(contents, 0, ScalarReal(internal->beta));
  SET_VECTOR_ELT(contents, 1, ScalarInteger(internal->dim_I));
  SET_VECTOR_ELT(contents, 2, ScalarInteger(internal->dim_N));
  SET_VECTOR_ELT(contents, 3, ScalarInteger(internal->dim_n_IR));
  SET_VECTOR_ELT(contents, 4, ScalarInteger(internal->dim_n_SI));
  SET_VECTOR_ELT(contents, 5, ScalarInteger(internal->dim_p_SI));
  SET_VECTOR_ELT(contents, 6, ScalarInteger(internal->dim_R));
  SET_VECTOR_ELT(contents, 7, ScalarInteger(internal->dim_S));
  SET_VECTOR_ELT(contents, 8, ScalarReal(internal->I_ini));
  SEXP initial_I = PROTECT(allocVector(REALSXP, internal->dim_I));
  memcpy(REAL(initial_I), internal->initial_I, internal->dim_I * sizeof(double));
  SET_VECTOR_ELT(contents, 9, initial_I);
  SEXP initial_R = PROTECT(allocVector(REALSXP, internal->dim_R));
  memcpy(REAL(initial_R), internal->initial_R, internal->dim_R * sizeof(double));
  SET_VECTOR_ELT(contents, 10, initial_R);
  SEXP initial_S = PROTECT(allocVector(REALSXP, internal->dim_S));
  memcpy(REAL(initial_S), internal->initial_S, internal->dim_S * sizeof(double));
  SET_VECTOR_ELT(contents, 11, initial_S);
  SEXP N = PROTECT(allocVector(REALSXP, internal->dim_N));
  memcpy(REAL(N), internal->N, internal->dim_N * sizeof(double));
  SET_VECTOR_ELT(contents, 12, N);
  SEXP n_IR = PROTECT(allocVector(REALSXP, internal->dim_n_IR));
  memcpy(REAL(n_IR), internal->n_IR, internal->dim_n_IR * sizeof(double));
  SET_VECTOR_ELT(contents, 13, n_IR);
  SEXP n_SI = PROTECT(allocVector(REALSXP, internal->dim_n_SI));
  memcpy(REAL(n_SI), internal->n_SI, internal->dim_n_SI * sizeof(double));
  SET_VECTOR_ELT(contents, 14, n_SI);
  SET_VECTOR_ELT(contents, 15, ScalarInteger(internal->nsim));
  SET_VECTOR_ELT(contents, 16, ScalarInteger(internal->offset_variable_R));
  SET_VECTOR_ELT(contents, 17, ScalarReal(internal->p_IR));
  SEXP p_SI = PROTECT(allocVector(REALSXP, internal->dim_p_SI));
  memcpy(REAL(p_SI), internal->p_SI, internal->dim_p_SI * sizeof(double));
  SET_VECTOR_ELT(contents, 18, p_SI);
  SET_VECTOR_ELT(contents, 19, ScalarReal(internal->S_ini));
  SET_VECTOR_ELT(contents, 20, ScalarReal(internal->sigma));
  SEXP nms = PROTECT(allocVector(STRSXP, 21));
  SET_STRING_ELT(nms, 0, mkChar("beta"));
  SET_STRING_ELT(nms, 1, mkChar("dim_I"));
  SET_STRING_ELT(nms, 2, mkChar("dim_N"));
  SET_STRING_ELT(nms, 3, mkChar("dim_n_IR"));
  SET_STRING_ELT(nms, 4, mkChar("dim_n_SI"));
  SET_STRING_ELT(nms, 5, mkChar("dim_p_SI"));
  SET_STRING_ELT(nms, 6, mkChar("dim_R"));
  SET_STRING_ELT(nms, 7, mkChar("dim_S"));
  SET_STRING_ELT(nms, 8, mkChar("I_ini"));
  SET_STRING_ELT(nms, 9, mkChar("initial_I"));
  SET_STRING_ELT(nms, 10, mkChar("initial_R"));
  SET_STRING_ELT(nms, 11, mkChar("initial_S"));
  SET_STRING_ELT(nms, 12, mkChar("N"));
  SET_STRING_ELT(nms, 13, mkChar("n_IR"));
  SET_STRING_ELT(nms, 14, mkChar("n_SI"));
  SET_STRING_ELT(nms, 15, mkChar("nsim"));
  SET_STRING_ELT(nms, 16, mkChar("offset_variable_R"));
  SET_STRING_ELT(nms, 17, mkChar("p_IR"));
  SET_STRING_ELT(nms, 18, mkChar("p_SI"));
  SET_STRING_ELT(nms, 19, mkChar("S_ini"));
  SET_STRING_ELT(nms, 20, mkChar("sigma"));
  setAttrib(contents, R_NamesSymbol, nms);
  UNPROTECT(9);
  return contents;
}
SEXP sir_stochastic_set_user(SEXP internal_p, SEXP user) {
  sir_stochastic_internal *internal = sir_stochastic_get_internal(internal_p, 1);
  internal->beta = user_get_scalar_double(user, "beta", internal->beta, NA_REAL, NA_REAL);
  internal->I_ini = user_get_scalar_double(user, "I_ini", internal->I_ini, NA_REAL, NA_REAL);
  internal->nsim = user_get_scalar_int(user, "nsim", internal->nsim, NA_REAL, NA_REAL);
  internal->S_ini = user_get_scalar_double(user, "S_ini", internal->S_ini, NA_REAL, NA_REAL);
  internal->sigma = user_get_scalar_double(user, "sigma", internal->sigma, NA_REAL, NA_REAL);
  internal->dim_I = internal->nsim;
  internal->dim_N = internal->nsim;
  internal->dim_n_IR = internal->nsim;
  internal->dim_n_SI = internal->nsim;
  internal->dim_p_SI = internal->nsim;
  internal->dim_R = internal->nsim;
  internal->dim_S = internal->nsim;
  internal->p_IR = 1 - exp(-(internal->sigma));
  Free(internal->initial_I);
  internal->initial_I = (double*) Calloc(internal->dim_I, double);
  Free(internal->initial_R);
  internal->initial_R = (double*) Calloc(internal->dim_R, double);
  Free(internal->initial_S);
  internal->initial_S = (double*) Calloc(internal->dim_S, double);
  Free(internal->N);
  internal->N = (double*) Calloc(internal->dim_N, double);
  Free(internal->n_IR);
  internal->n_IR = (double*) Calloc(internal->dim_n_IR, double);
  Free(internal->n_SI);
  internal->n_SI = (double*) Calloc(internal->dim_n_SI, double);
  Free(internal->p_SI);
  internal->p_SI = (double*) Calloc(internal->dim_p_SI, double);
  for (int i = 1; i <= internal->dim_I; ++i) {
    internal->initial_I[i - 1] = internal->I_ini;
  }
  for (int i = 1; i <= internal->dim_R; ++i) {
    internal->initial_R[i - 1] = 0;
  }
  for (int i = 1; i <= internal->dim_S; ++i) {
    internal->initial_S[i - 1] = internal->S_ini;
  }
  internal->offset_variable_R = internal->dim_I + internal->dim_S;
  return R_NilValue;
}
SEXP sir_stochastic_set_initial(SEXP internal_p, SEXP step_ptr, SEXP state_ptr) {
  return R_NilValue;
}
SEXP sir_stochastic_metadata(SEXP internal_p) {
  sir_stochastic_internal *internal = sir_stochastic_get_internal(internal_p, 1);
  SEXP ret = PROTECT(allocVector(VECSXP, 4));
  SEXP nms = PROTECT(allocVector(STRSXP, 4));
  SET_STRING_ELT(nms, 0, mkChar("variable_order"));
  SET_STRING_ELT(nms, 1, mkChar("output_order"));
  SET_STRING_ELT(nms, 2, mkChar("n_out"));
  SET_STRING_ELT(nms, 3, mkChar("interpolate_t"));
  setAttrib(ret, R_NamesSymbol, nms);
  SEXP variable_length = PROTECT(allocVector(VECSXP, 3));
  SEXP variable_names = PROTECT(allocVector(STRSXP, 3));
  setAttrib(variable_length, R_NamesSymbol, variable_names);
  SET_VECTOR_ELT(variable_length, 0, ScalarInteger(internal->dim_S));
  SET_VECTOR_ELT(variable_length, 1, ScalarInteger(internal->dim_I));
  SET_VECTOR_ELT(variable_length, 2, ScalarInteger(internal->dim_R));
  SET_STRING_ELT(variable_names, 0, mkChar("S"));
  SET_STRING_ELT(variable_names, 1, mkChar("I"));
  SET_STRING_ELT(variable_names, 2, mkChar("R"));
  SET_VECTOR_ELT(ret, 0, variable_length);
  UNPROTECT(2);
  SET_VECTOR_ELT(ret, 1, R_NilValue);
  SET_VECTOR_ELT(ret, 2, ScalarInteger(0));
  UNPROTECT(2);
  return ret;
}
SEXP sir_stochastic_initial_conditions(SEXP internal_p, SEXP step_ptr) {
  sir_stochastic_internal *internal = sir_stochastic_get_internal(internal_p, 1);
  SEXP r_state = PROTECT(allocVector(REALSXP, internal->dim_I + internal->dim_R + internal->dim_S));
  double * state = REAL(r_state);
  memcpy(state + 0, internal->initial_S, internal->dim_S * sizeof(double));
  memcpy(state + internal->dim_S, internal->initial_I, internal->dim_I * sizeof(double));
  memcpy(state + internal->offset_variable_R, internal->initial_R, internal->dim_R * sizeof(double));
  UNPROTECT(1);
  return r_state;
}
void sir_stochastic_rhs(sir_stochastic_internal* internal, size_t step, double * state, double * state_next, double * output) {
  double * S = state + 0;
  double * I = state + internal->dim_S;
  double * R = state + internal->offset_variable_R;
  for (int i = 1; i <= internal->dim_N; ++i) {
    internal->N[i - 1] = S[i - 1] + I[i - 1] + R[i - 1];
  }
  for (int i = 1; i <= internal->dim_n_IR; ++i) {
    internal->n_IR[i - 1] = Rf_rbinom(round(I[i - 1]), internal->p_IR);
  }
  for (int i = 1; i <= internal->dim_p_SI; ++i) {
    internal->p_SI[i - 1] = 1 - exp(-(internal->beta) * I[i - 1] / (double) internal->N[i - 1]);
  }
  for (int i = 1; i <= internal->dim_R; ++i) {
    state_next[internal->offset_variable_R + i - 1] = R[i - 1] + internal->n_IR[i - 1];
  }
  for (int i = 1; i <= internal->dim_n_SI; ++i) {
    internal->n_SI[i - 1] = Rf_rbinom(round(S[i - 1]), internal->p_SI[i - 1]);
  }
  for (int i = 1; i <= internal->dim_I; ++i) {
    state_next[internal->dim_S + i - 1] = I[i - 1] + internal->n_SI[i - 1] - internal->n_IR[i - 1];
  }
  for (int i = 1; i <= internal->dim_S; ++i) {
    state_next[0 + i - 1] = S[i - 1] - internal->n_SI[i - 1];
  }
}
void sir_stochastic_rhs_dde(size_t n_eq, size_t step, double * state, double * state_next, size_t n_out, double * output, void * internal) {
  sir_stochastic_rhs((sir_stochastic_internal*)internal, step, state, state_next, output);
}
SEXP sir_stochastic_rhs_r(SEXP internal_p, SEXP step, SEXP state) {
  SEXP state_next = PROTECT(allocVector(REALSXP, LENGTH(state)));
  sir_stochastic_internal *internal = sir_stochastic_get_internal(internal_p, 1);
  double *output = NULL;
  GetRNGstate();
  sir_stochastic_rhs(internal, scalar_int(step, "step"), REAL(state), REAL(state_next), output);
  PutRNGstate();
  UNPROTECT(1);
  return state_next;
}
double user_get_scalar_double(SEXP user, const char *name,
                              double default_value, double min, double max) {
  double ret = default_value;
  SEXP el = user_list_element(user, name);
  if (el != R_NilValue) {
    if (length(el) != 1) {
      Rf_error("Expected a scalar numeric for '%s'", name);
    }
    if (TYPEOF(el) == REALSXP) {
      ret = REAL(el)[0];
    } else if (TYPEOF(el) == INTSXP) {
      ret = INTEGER(el)[0];
    } else {
      Rf_error("Expected a numeric value for %s", name);
    }
  }
  if (ISNA(ret)) {
    Rf_error("Expected a value for '%s'", name);
  }
  user_check_values_double(&ret, 1, min, max, name);
  return ret;
}
int user_get_scalar_int(SEXP user, const char *name,
                        int default_value, double min, double max) {
  int ret = default_value;
  SEXP el = user_list_element(user, name);
  if (el != R_NilValue) {
    if (length(el) != 1) {
      Rf_error("Expected scalar integer for %d", name);
    }
    if (TYPEOF(el) == REALSXP) {
      double tmp = REAL(el)[0];
      if (fabs(tmp - round(tmp)) > 2e-8) {
        Rf_error("Expected '%s' to be integer-like", name);
      }
    }
    ret = INTEGER(coerceVector(el, INTSXP))[0];
  }
  if (ret == NA_INTEGER) {
    Rf_error("Expected a value for '%s'", name);
  }
  user_check_values_int(&ret, 1, min, max, name);
  return ret;
}
void user_check_values_double(double * value, size_t len,
                                  double min, double max, const char *name) {
  for (size_t i = 0; i < len; ++i) {
    if (ISNA(value[i])) {
      Rf_error("'%s' must not contain any NA values", name);
    }
  }
  if (min != NA_REAL) {
    for (size_t i = 0; i < len; ++i) {
      if (value[i] < min) {
        Rf_error("Expected '%s' to be at least %g", name, min);
      }
    }
  }
  if (max != NA_REAL) {
    for (size_t i = 0; i < len; ++i) {
      if (value[i] > max) {
        Rf_error("Expected '%s' to be at most %g", name, max);
      }
    }
  }
}
void user_check_values_int(int * value, size_t len,
                               double min, double max, const char *name) {
  for (size_t i = 0; i < len; ++i) {
    if (ISNA(value[i])) {
      Rf_error("'%s' must not contain any NA values", name);
    }
  }
  if (min != NA_REAL) {
    for (size_t i = 0; i < len; ++i) {
      if (value[i] < min) {
        Rf_error("Expected '%s' to be at least %g", name, min);
      }
    }
  }
  if (max != NA_REAL) {
    for (size_t i = 0; i < len; ++i) {
      if (value[i] > max) {
        Rf_error("Expected '%s' to be at most %g", name, max);
      }
    }
  }
}
void user_check_values(SEXP value, double min, double max,
                           const char *name) {
  size_t len = (size_t)length(value);
  if (TYPEOF(value) == INTSXP) {
    user_check_values_int(INTEGER(value), len, min, max, name);
  } else {
    user_check_values_double(REAL(value), len, min, max, name);
  }
}
SEXP user_list_element(SEXP list, const char *name) {
  SEXP ret = R_NilValue, names = getAttrib(list, R_NamesSymbol);
  for (int i = 0; i < length(list); ++i) {
    if (strcmp(CHAR(STRING_ELT(names, i)), name) == 0) {
      ret = VECTOR_ELT(list, i);
      break;
    }
  }
  return ret;
}
int scalar_int(SEXP x, const char * name) {
  if (Rf_length(x) != 1) {
    Rf_error("Expected a scalar for %s", name);
  }
  int ret = 0;
  if (TYPEOF(x) == INTSXP) {
    ret = INTEGER(x)[0];
  } else if (TYPEOF(x) == REALSXP) {
    double rx = REAL(x)[0];
    ret = rx;
    if (fabs(rx - ret) > sqrt(DOUBLE_EPS)) {
      Rf_error("Expected a integer-like for %s", name);
    }
  } else {
    Rf_error("Expected an integer value for %s", name);
  }
  return ret;
}
