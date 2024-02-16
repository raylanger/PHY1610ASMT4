#include "root.h"
#include "multivariate.h"

// Create polynomial function
int multivariate_eq(const gsl_vector * vec, void* p, gsl_vector * func){

    // Assign pointer p to func_params structure holding parameters 
    struct func_params * params = (struct func_params *)p;

    // Get individual parameters
    double k1 = (params->k1);
    double k2 = (params->k2);
    double x0 = (params->x0);
    double y0 = (params->y0);
    double z0 = (params->z0);

    // Define c1 and c2
    double c1 = x0 - 2*y0;
    double c2 = x0 + z0;

    // Get independent variables from input vector
    const double x = gsl_vector_get (vec, 0);
    const double y = gsl_vector_get (vec, 1);
    const double z = gsl_vector_get (vec, 2);

    // Get three equations to be solved (each one should be equal to zero)
    const double eq0 = k1 * std::pow(x,2)*y - k2*std::pow(z,2);
    const double eq1 = c1+2*y-x;
    const double eq2 = c2-x-z;

    // Set vector func to contain values of 3 equations
    gsl_vector_set (func, 0, eq0);
    gsl_vector_set (func, 1, eq1);
    gsl_vector_set (func, 2, eq2);

    return GSL_SUCCESS;
    
}

void output_state (int iter, gsl_multiroot_fsolver * s)
{
  printf ("iter = %3d   x = % .8f   y = % .8f   z = % .8f"
          "       f(x) = [% .3e, % .3e, % .3e]\n",
          iter,
          gsl_vector_get (s->x, 0),
          gsl_vector_get (s->x, 1),
          gsl_vector_get (s->x, 2),
          gsl_vector_get (s->f, 0),
          gsl_vector_get (s->f, 1),
          gsl_vector_get (s->f, 2));
}