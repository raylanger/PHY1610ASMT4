#include "root.h"
#include "polynomial.h"
#include "multivariate.h"

int main(int argc, char* argv[]){

      int func_type = 0; //Initialize variable for determining polynomial vs multivariate functions (0 for polynomial, 1 for mlutivariate)

      struct func_params f_params = {1.0, 0.7, 0.5,1.0,0.0}; //Initialize parameters

      try {
            if (argc > 1)
                  if (argv[1] != "0") func_type = 1;
            if (argc > 2)
                  f_params.k1 = std::stod(argv[2]);
            if (argc > 3)
                  f_params.k2 = std::stod(argv[3]);
            if (argc > 4)
                  f_params.x0 = std::stod(argv[4]);
            if (argc > 5)
                  f_params.y0 = std::stod(argv[5]);
            if (argc > 6)
                  f_params.z0 = std::stod(argv[6]);
      } catch(...) {
            std::cout <<
                  "Computes the final concentrations of a chemical reaction given by 2X + Y ⇌ 2Z," 
                  "with given forward/backward reaction rates and initial concentrations. By default, the polynomial function is"
                  "used to find the root, and to use the multivariate equations, run ASMT4 followed by any string other than '0'.\n\n"
                  "Usage:\n"
                  "  ASMT4 [-h | --help] | [FUNC_TYPE [FORWARD_RATE [BACKWARD_RATE [X_CONCENTRATION [Y_CONCENTRATION [Z_CONCENTRATION]]]]]]\n\n";
            if (std::string(argv[1]) != "-h" and std::string(argv[1]) !="--help") {
                  std::cerr << "Error in arguments!\n";
                  return 1;
            } else
                  return 0;
      }

      if (func_type == 0){
            int status = polynomial_root(f_params);

            return status;
      }else{
            int status = multivariate_root(f_params);
            
            return status;
      }
}