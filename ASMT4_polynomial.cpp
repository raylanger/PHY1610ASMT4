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