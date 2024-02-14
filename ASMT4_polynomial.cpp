#include <gsl/gsl_roots.h>
#include <iostream>
#include <cmath>

// Create strucure to hold function parameters
struct func_params {double k1; double k2; double x0; double y0; double z0;};

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

    return k1*std::pow(x,3) - (c1*k1+2*k2)*std::pow(x,2) + 4*c2*k2*x - 2*k2*std::pow(c2,2);
}

int main(int argc, char* argv[]){
    struct func_params f_params;

    f_params.k1 = 1.0;
    f_params.k2 = 0.7;
    f_params.x0 = 0.5;
    f_params.y0 = 1;
    f_params.z0 = 0;

    for (float x = 0; x<2; x+=0.25){
        double val = polynomial_eq(x,&f_params);

        std::cout << val << "\n";
    }
    return 1;
}
