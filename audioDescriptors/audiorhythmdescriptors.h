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
    BeatHistogramDescriptorExtractor(CorrelationFunction &c_func, double koeff, int ticks_count = 3);
    double getTempID(double bmp);
    std::vector<double> extract();
    AudioDescriptorExtractor* clone() const;

};




#endif // AUDIORHYTHMDESCRIPTORS_H
