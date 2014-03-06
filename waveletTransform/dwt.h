#ifndef DWT_H
#define DWT_H

#include <vector>
#include <gsl/gsl_wavelet.h>
#include <iostream>
#include "tools.h"

class DWT{
public:
    static bool Forward(std::vector<double> Input, std::vector<double> &Output);
};

#endif // DWT_H
