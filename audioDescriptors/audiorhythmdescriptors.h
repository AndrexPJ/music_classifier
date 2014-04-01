#ifndef AUDIORHYTHMDESCRIPTORS_H
#define AUDIORHYTHMDESCRIPTORS_H
#include "audioDescriptors/audiodescriptorextractor.h"
#include "audioDescriptors/audiospectrumdescriptors.h"
#include "specialFunctions/noveltyfunctions.h"
#include "specialFunctions/correlationfunctions.h"
#include "fastFourierTransform/fft.h"
#include <vector>
#include <tools.h>



class BeatHistogramDescriptorExtractor : public MainTicksDescriptorExtractor{
private:
    int max_bmp, min_bmp;
    double koeff;
public:
    BeatHistogramDescriptorExtractor(CorrelationFunction &c_func, double koeff, int ticks_count = 5);
    std::vector<double> extract();

};




#endif // AUDIORHYTHMDESCRIPTORS_H
