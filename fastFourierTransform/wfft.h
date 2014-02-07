#ifndef WFFT_H
#define WFFT_H

#include "fft.h"
#include "vector"
#include "windowfunctions.h"
#include <iostream>
#include "tools.h"
class WFFT
{
public:
    static bool perform(const std::vector<double> &Input, std::vector< std::vector<complex> > &Output,WindowFunction &window,int window_Size, int hop_size);
};

#endif // WFFT_H
