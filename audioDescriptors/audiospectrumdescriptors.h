#ifndef AUDIOSPECTRUMDESCRIPTORS_H
#define AUDIOSPECTRUMDESCRIPTORS_H

#include "audioDescriptors/audiodescriptorextractor.h"
#include "audioTransforms/audiospectrumtransforms.h"

class SpCentroidDescriptorExtractor : AudioDescriptorExtractor{
private:
    AudioAmpSpectrum spectrum;
public:
    SpCentroidDescriptorExtractor(AudioAmpSpectrum &spectrum);
    std::vector<double> extract();
};


class SpFlatnessDescriptorExtractor : AudioDescriptorExtractor{
private:
    AudioAmpSpectrum spectrum;
public:
    SpFlatnessDescriptorExtractor(AudioAmpSpectrum &spectrum);
    std::vector<double> extract();

};

class SpFluxDescriptorExtractor : AudioDescriptorExtractor{
private:
    AudioSpectrum<complex> spectrum;
public:
    SpFluxDescriptorExtractor(AudioSpectrum<complex> &spectrum);
    std::vector<double> extract();
};

#endif // AUDIOSPECTRUMDESCRIPTORS_H