#ifndef AUDIOTONALITYDESCRIPTORS_H
#define AUDIOTONALITYDESCRIPTORS_H

#include "featureExtractionLibraries/audioDescriptors/audiodescriptorextractor.h"
#include "featureExtractionLibraries/audioDescriptors/audiospectrumdescriptors.h"

class MainPitchesDescriptorExtractor : public MainTicksDescriptorExtractor {
protected:
    int pitches_count;
public:
    MainPitchesDescriptorExtractor(AudioPitchChroma &pitch_chroma, int pitches_count = 1);
    std::vector<double> extract();
    AudioDescriptorExtractor* clone();
};


#endif // AUDIOTONALITYDESCRIPTORS_H
