#ifndef AUDIODESCRIPTORS_H
#define AUDIODESCRIPTORS_H

#include "audioDescriptors/audiodescriptorextractor.h"


class EnergyDescriptorExtractor : public AudioDescriptorExtractor {
private:
    AudioRecord record;
public:
    EnergyDescriptorExtractor(AudioRecord &record);
    std::vector<double> extract();
    AudioDescriptorExtractor* clone() const;
};


class ZCRDescriptorExtractor : public AudioDescriptorExtractor {
private:
    AudioRecord record;
public:
    ZCRDescriptorExtractor(AudioRecord &record);
    std::vector<double> extract();
    AudioDescriptorExtractor* clone() const;
};




#endif // AUDIODESCRIPTORS_H
