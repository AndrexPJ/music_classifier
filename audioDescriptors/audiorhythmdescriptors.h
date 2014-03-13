#ifndef AUDIORHYTHMDESCRIPTORS_H
#define AUDIORHYTHMDESCRIPTORS_H
#include "audioDescriptors/audiodescriptorextractor.h"
#include "specialFunctions/noveltyfunctions.h"
#include "specialFunctions/correlationfunctions.h"
#include "fastFourierTransform/fft.h"
#include <vector>
#include <tools.h>



class BeatHistogramDescriptorExtractor : public AudioDescriptorExtractor{
private:
    int max_bmp, min_bmp;
    std::vector<double> histogram;
    int histogram_size;
    double koeff;
public:
    BeatHistogramDescriptorExtractor(CorrelationFunction &c_func, double koeff);
    std::vector<double> extract();

};




#endif // AUDIORHYTHMDESCRIPTORS_H
