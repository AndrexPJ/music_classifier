#ifndef AUDIOSPECTRUM_H
#define AUDIOSPECTRUM_H

#include "basicClasses/audiodata.h"
#include "fastFourierTransform/complex.h"

class AudioSpectrum : AudioData<complex>
{
public:
    int channelsCount, channelDataSize;
    double frequencyStep;
    AudioSpectrum();

    complex getFrequency(int n);
};

#endif // AUDIOSPECTRUM_H
