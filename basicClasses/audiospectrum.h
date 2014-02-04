#ifndef AUDIOSPECTRUM_H
#define AUDIOSPECTRUM_H

#include "basicClasses/audiodata.h"

class AudioSpectrum : AudioData
{
public:
    int channelsCount, channelDataSize;
    double frequencyStep;
    AudioSpectrum();

    double getFrequency(int n);
};

#endif // AUDIOSPECTRUM_H
