#include "audiospectrum.h"

AudioSpectrum::AudioSpectrum()
{
    this->channelDataSize = 0;
    this->channelsCount = 0;
}


complex AudioSpectrum::getFrequency(int n){
    return this->frequencyStep * n;
}
