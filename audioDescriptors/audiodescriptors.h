#ifndef AUDIODESCRIPTORS_H
#define AUDIODESCRIPTORS_H

#include "audioDescriptors/audiodescriptorextractor.h"
#include "audioTransforms/audiospectrumtransforms.h"
#include <math.h>
#include <iostream>


class EnergyDescriptorExtractor : AudioDescriptorExtractor {
private:
    AudioRecord record;
public:
    EnergyDescriptorExtractor(AudioRecord &record);
    std::vector<double> extract();
};


class ZCRDescriptorExtractor : AudioDescriptorExtractor {
private:
    AudioRecord record;
public:
    ZCRDescriptorExtractor(AudioRecord &record);
    std::vector<double> extract();
};


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

#endif // AUDIODESCRIPTORS_H
