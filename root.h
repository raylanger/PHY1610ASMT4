#ifndef ROOTH
#define ROOTH

#include <gsl/gsl_roots.h>
#include <gsl/gsl_errno.h>
#include <cmath>
#include <stdio.h>
#include <iostream>

// Create strucure to hold function parameters
struct func_params {double k1; double k2; double x0; double y0; double z0;};

#endif