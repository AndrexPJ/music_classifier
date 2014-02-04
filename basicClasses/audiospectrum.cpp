#include "audiospectrum.h"

AudioSpectrum::AudioSpectrum() : AudioData()
{
    this->channelDataSize = 0;
    this->channelsCount = 0;
}


double AudioSpectrum::getFrequency(int n){
    return this->frequencyStep * n;
}
