#ifndef AUDIOTONALITYDESCRIPTORS_H
#define AUDIOTONALITYDESCRIPTORS_H

#include "audioDescriptors/audiodescriptorextractor.h"
#include "audioDescriptors/audiospectrumdescriptors.h"

class MainPitchDescriptorExtractor : public HistogramDescriptorExtractor {
protected:
    int pitches_count;
public:
    MainPitchDescriptorExtractor(AudioPitchChroma &pitch_chroma, int pitches_count = 1);
    std::vector<double> extract();
};


#endif // AUDIOTONALITYDESCRIPTORS_H
