#ifndef WFFT_H
#define WFFT_H

#include "fft.h"
#include "vector"
#include "windowfunctions.h"
#include <iostream>
class WFFT
{
public:
    static bool perform(const std::vector<double> &Input, std::vector<complex> &Output,WindowFunction *window,int Window_Size, int Offset = 0);
};

#endif // WFFT_H
