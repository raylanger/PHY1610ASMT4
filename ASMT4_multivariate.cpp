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

void output_mv_state (int iter, gsl_multiroot_fsolver * s)
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

int multivariate_root(struct func_params f_params){

    const gsl_multiroot_fsolver_type *T; //Define pointer to point to algorithm type
    gsl_multiroot_fsolver *s; //Define pointer to point to function solver

    int status; //Initiailze status variable
    int iter = 0; //Initialize iteration counter

    gsl_multiroot_function f = {&multivariate_eq, 3, &f_params}; // Create 3-d multivariate function with f_params

    double x_init[3] = {f_params.x0, f_params.y0,f_params.z0}; //Set initial values
    gsl_vector *vec = gsl_vector_alloc (3); // Initialize vector to hold values

    // Assign initial values to vec
    gsl_vector_set (vec, 0, x_init[0]);
    gsl_vector_set (vec, 1, x_init[1]);
    gsl_vector_set (vec, 2, x_init[2]);

    
    T = gsl_multiroot_fsolver_hybrids; //Assign T to hybrid type
    s = gsl_multiroot_fsolver_alloc (T, 3); //Assign s to be fsolver with type T and 3-dimensions
    gsl_multiroot_fsolver_set (s, &f, vec); //Assign function f (with params) and initial vector s

    output_mv_state (iter, s); //Print initial state

    do //While loop until root found or iterations exceeds max_iter
    {
            iter++; //Iterate iter
            status = gsl_multiroot_fsolver_iterate (s); //Iterate solver

            output_mv_state (iter, s); //Print current state

            if (status)   // check if solver is stuck 
            break;

            status = gsl_multiroot_test_residual (s->f, 1e-6); //Set status == GSL_SUCCESS if error less than 1e-6
    }
    while (status == GSL_CONTINUE && iter < 1000);

    printf ("status = %s\n", gsl_strerror (status)); // Print status of root finding

    // Free memory
    gsl_multiroot_fsolver_free (s);     
    gsl_vector_free (vec);

    return status;
}