#ifndef AUDIORHYTHMDESCRIPTORS_H
#define AUDIORHYTHMDESCRIPTORS_H

#include "featureExtractionLibraries/audioDescriptors/audiodescriptorextractor.h"
#include "featureExtractionLibraries/audioDescriptors/audiospectrumdescriptors.h"
#include "featureExtractionLibraries/specialFunctions/noveltyfunctions.h"
#include "featureExtractionLibraries/specialFunctions/correlationfunctions.h"
#include "featureExtractionLibraries/fastFourierTransform/fft.h"
#include <vector>
#include "tools/tools.h"



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
