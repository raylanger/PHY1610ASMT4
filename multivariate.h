#ifndef MULTIVARIATEH
#define MULTIVARIATEH

#include <gsl/gsl_vector.h>
#include <gsl/gsl_multiroots.h>

int multivariate_eq(const gsl_vector * x, void* p, gsl_vector * f);
void output_state (int iter, gsl_multiroot_fsolver * s);

#endif