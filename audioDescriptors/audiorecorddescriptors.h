#ifndef AUDIODESCRIPTORS_H
#define AUDIODESCRIPTORS_H

#include "audioDescriptors/audiodescriptorextractor.h"

class EnergyDescriptorExtractor : public AudioDescriptorExtractor {
private:
    AudioRecord record;
    bool fillResult();
public:
    EnergyDescriptorExtractor(AudioRecord &record);
};


class ZCRDescriptorExtractor : public AudioDescriptorExtractor {
private:
    AudioRecord record;
    bool fillResult();
public:
    ZCRDescriptorExtractor(AudioRecord &record);
};




#endif // AUDIODESCRIPTORS_H
