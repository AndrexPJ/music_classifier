#ifndef WFFT_H
#define WFFT_H

#include <iostream>
#include <vector>

#include "featureExtractionLibraries/specialFunctions/windowfunctions.h"
#include "featureExtractionLibraries/fastFourierTransform/fft.h"
#include "tools/tools.h"

class WFFT
{
public:
    static bool perform(const std::vector<double> &Input, std::vector< std::vector<complex> > &Output,WindowFunction &window,int window_Size, int hop_size);
};

#endif // WFFT_H
