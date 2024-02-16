#include "root.h"
#include "polynomial.h"
#include <stdio.h>
#include <gsl/gsl_errno.h>

int main(int argc, char* argv[]){
      struct func_params f_params = {1.0, 0.7, 0.5,1.0,0.0}; //Initialize parameters

      try {
            if (argc > 1)
                  f_params.k1 = std::stod(argv[1]);
            if (argc > 2)
                  f_params.k2 = std::stod(argv[2]);
            if (argc > 3)
                  f_params.x0 = std::stod(argv[3]);
            if (argc > 4)
                  f_params.y0 = std::stod(argv[4]);
            if (argc > 5)
                  f_params.z0 = std::stod(argv[5]);
      } catch(...) {
            std::cout <<
                  "Computes the final concentrations of a chemical reaction given by 2X + Y ⇌ 2Z," 
                  "with given forward/backward reaction rates and initial concentrations.\n\n"
                  "Usage:\n"
                  "  ASMT4 [-h | --help] | [FORWARD_RATE [BACKWARD_RATE [X_CONCENTRATION [Y_CONCENTRATION [Z_CONCENTRATION]]]]]\n\n";
            if (std::string(argv[1]) != "-h" and std::string(argv[1]) !="--help") {
                  std::cerr << "Error in arguments!\n";
                  return 1;
            } else
                  return 0;
      }
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

      printf ("%10s [%12s, %12s] %10s %12s\n",
            "Iteration", "Lower Bound", "Upper Bound", "Root",
            "Error"); //Define columns for output

      do { //While loop
            iter++; // Iterate
            status = gsl_root_fsolver_iterate (s); // Iterate
            x = gsl_root_fsolver_root (s); // Get root estimate
            x_lo = gsl_root_fsolver_x_lower (s); // Get lower bound
            x_hi = gsl_root_fsolver_x_upper (s); // Get upper bound
            status = gsl_root_test_interval (x_lo, x_hi,
                                          0, 1e-6); // Set status as GSL_SUCCESS if x_lo, x_hi within 1e-6 of each other

            if (status == GSL_SUCCESS)
            printf ("Converged:\n");

            printf ("%5d      [%.10f, %.10f] %.8f %+.5e\n",
                  iter, x_lo, x_hi,
                  x, x_hi-x_lo); //Print results
      }while (status == GSL_CONTINUE && iter < max_iter);

      if (status == GSL_SUCCESS){
            double y = -0.5*(f_params.x0 - 2*f_params.y0 - x);
            double z = f_params.x0 + f_params.z0 - x;
            printf("Root found at [x] = %.8f, [y] = %.8f, [z] = %.8f.\n", x,y,z);
      } else {
            printf("Root could not be found in %d iterations.", max_iter);
      }

      gsl_root_fsolver_free (s); // Free memory associated with s

      return status;
}