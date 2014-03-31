#ifndef AUDIOTONALITYDESCRIPTORS_H
#define AUDIOTONALITYDESCRIPTORS_H

#include "audioDescriptors/audiodescriptorextractor.h"
#include "audioDescriptors/audiospectrumdescriptors.h"

class MainPitchesDescriptorExtractor : public MainTicksDescriptorExtractor {
protected:
    int pitches_count;
public:
    MainPitchesDescriptorExtractor(AudioPitchChroma &pitch_chroma, int pitches_count = 1);
};


#endif // AUDIOTONALITYDESCRIPTORS_H
