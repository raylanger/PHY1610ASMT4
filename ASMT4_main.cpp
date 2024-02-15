#include "root.h"
#include "polynomial.h"
#include <stdio.h>
#include <gsl/gsl_errno.h>

int main(){
      int status; //Initiailze status variable
      int iter = 0, max_iter = 100; //Initialize iteration counter, set maximum iterations

      double x = 0; //Initialize independent variable, define expected root
      double x_lo = 0.0, x_hi = 1.0; //Define bounds of searching region

      struct func_params f_params = {1.0, 0.7, 0.5,1.0,0.0}; //Initialize parameters

      gsl_function F; // Initialize root finding function

      F.function = &polynomial_eq; //Set function to polynomial
      F.params = &f_params; //Set parameters of function

      const gsl_root_fsolver_type *T; //Define pointer to point to algorithm type
      gsl_root_fsolver *s; //Define pointer to point to function solver

      T = gsl_root_fsolver_brent; //Set solver type to be brent
      s = gsl_root_fsolver_alloc(T); //Create solver of correct type

      gsl_root_fsolver_set (s, &F, x_lo, x_hi); //Assign function F (with params) and search interval to s

      do { //While loop
            iter++; // Iterate
            status = gsl_root_fsolver_iterate (s); // Iterate
            x = gsl_root_fsolver_root (s); // Get root estimate
            x_lo = gsl_root_fsolver_x_lower (s); // Get lower bound
            x_hi = gsl_root_fsolver_x_upper (s); // Get upper bound
            status = gsl_root_test_interval (x_lo, x_hi,
                                          0, 1e-6); // Set status as GSL_SUCCESS if x_lo, x_hi within 1e-6 of each other
      }while (status == GSL_CONTINUE && iter < max_iter);

      if (status == GSL_SUCCESS){
            printf("Root found at x = %.8f.\n", x);
      } else {
            printf("Root could not be found in %d iterations.", max_iter);
      }

      gsl_root_fsolver_free (s); // Free memory associated with s

      return status;
}