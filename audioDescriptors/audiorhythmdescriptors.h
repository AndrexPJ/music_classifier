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
    std::vector<double> histogram;
    int histogram_size;
public:
    BeatHistogramDescriptorExtractor(CorrelationFunction &c_func);
    std::vector<double> extract();

};




#endif // AUDIORHYTHMDESCRIPTORS_H
