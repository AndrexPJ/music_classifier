#ifndef WFFT_H
#define WFFT_H


#include "specialFunctions/windowfunctions.h"
#include "fastFourierTransform/fft.h"
#include "tools.h"
#include <iostream>
#include <vector>
class WFFT
{
public:
    static bool perform(const std::vector<double> &Input, std::vector< std::vector<complex> > &Output,WindowFunction &window,int window_Size, int hop_size);
};

#endif // WFFT_H
