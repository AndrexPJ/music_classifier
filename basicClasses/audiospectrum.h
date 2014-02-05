#ifndef AUDIOSPECTRUM_H
#define AUDIOSPECTRUM_H

#include "basicClasses/audiodata.h"
#include "fastFourierTransform/complex.h"

template <class T>
class AudioSpectrum : public AudioData<T>
{
public:
    AudioSpectrum();

    double getFrequency(int n);
};


template <class T>
AudioSpectrum<T>::AudioSpectrum()
{
    this->channelDataSize = 0;
    this->channelsCount = 0;
}

template <class T>
double AudioSpectrum<T>::getFrequency(int n){
    return this->frequencyStep * n;
}


#endif // AUDIOSPECTRUM_H
