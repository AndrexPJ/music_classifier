#ifndef AUDIODESCRIPTORS_H
#define AUDIODESCRIPTORS_H

#include "featureExtractionLibraries/audioDescriptors/audiodescriptorextractor.h"

class EnergyDescriptorExtractor : public AudioDescriptorExtractor {
private:
    AudioRecord record;
public:
    EnergyDescriptorExtractor(AudioRecord &record);
    std::vector<double> extract();
    AudioDescriptorExtractor* clone();
};


class ZCRDescriptorExtractor : public AudioDescriptorExtractor {
private:
    AudioRecord record;
public:
    ZCRDescriptorExtractor(AudioRecord &record);
    std::vector<double> extract();
    AudioDescriptorExtractor* clone();
};



#endif // AUDIODESCRIPTORS_H
