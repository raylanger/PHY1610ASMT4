#ifndef POLYNOMIALH
#define POLYNOMIALH


double polynomial_eq(double x, void* p);
int output_pn_state(int iter, gsl_root_fsolver * s, struct func_params f_params);
int polynomial_root(struct func_params f_params);

#endif

