#include "root.h"
#include "polynomial.h"

// Create polynomial function
double polynomial_eq(double x, void* p){

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

    // Return value of polynomial
    return k1*std::pow(x,3) - (c1*k1+2*k2)*std::pow(x,2) + 4*c2*k2*x - 2*k2*std::pow(c2,2);
}

int output_pn_state(int iter, gsl_root_fsolver * s, struct func_params f_params){

    int status = gsl_root_fsolver_iterate (s); // Iterate
    double x = gsl_root_fsolver_root (s); // Get root estimate
    double x_lo = gsl_root_fsolver_x_lower (s); // Get lower bound
    double x_hi = gsl_root_fsolver_x_upper (s); // Get upper bound
    status = gsl_root_test_interval (x_lo, x_hi,
                                0, 1e-6); // Set status as GSL_SUCCESS if x_lo, x_hi within 1e-6 of each other

    double y = -0.5*(f_params.x0 - 2*f_params.y0 - x);
    double z = f_params.x0 + f_params.z0 - x;

    if (status == GSL_SUCCESS)
    printf ("Converged:\n");

    printf ("%5d      [%12f, %12f] %+.8f %+.8f %+.8f %+.5e\n",
        iter, x_lo, x_hi,
        x, y, z, x_hi-x_lo); //Print results

    return status;
}

int polynomial_root(struct func_params f_params){
    int status; //Initiailze status variable
    int iter = 0, max_iter = 100; //Initialize iteration counter, set maximum iterations

    double x = 0; //Initialize independent variable, define expected root
    double x_lo = -100.0, x_hi = 100.0; //Define bounds of searching region

    gsl_function F; // Initialize root finding function

    F.function = &polynomial_eq; //Set function to polynomial
    F.params = &f_params; //Set parameters of function

    const gsl_root_fsolver_type *T; //Define pointer to point to algorithm type
    gsl_root_fsolver *s; //Define pointer to point to function solver

    T = gsl_root_fsolver_brent; //Set solver type to be brent
    s = gsl_root_fsolver_alloc(T); //Create solver of correct type

    gsl_root_fsolver_set (s, &F, x_lo, x_hi); //Assign function F (with params) and search interval to s

    printf ("%10s [%12s, %12s] %11s %11s %11s %12s\n",
            "Iteration", "Lower Bound", "Upper Bound", "X-Value", "Y-Value", "Z-Value",
            "Error"); //Define columns for output

    do { //While loop
            iter++; // Iterate
            status = output_pn_state(iter, s, f_params);
    }while (status == GSL_CONTINUE && iter < max_iter);

    printf("status = %s\n", gsl_strerror(status)); // Print status of root finding

    gsl_root_fsolver_free (s); // Free memory associated with s

    return status;
}