#ifndef AUDIOSPECTRUM_H
#define AUDIOSPECTRUM_H

#include "basicClasses/audiodata.h"
#include "fastFourierTransform/complex.h"
#include <math.h>
#include <iostream>

template <class T>
class AudioSpectrum : public AudioData< std::vector<T> >
{
private:
    bool updateFrequencyStep();
public:
    AudioSpectrum();
    AudioSpectrum(const AudioSpectrum<T> &spectrum);
    double frequencyStep;
    int windowSize;
    double getFrequency(int n);
    bool setDataSize(int channels_count, int data_size);
    bool setSampleRate(int sample_rate);
    bool setWindowSize(int windows_size);
};



template <class T>
AudioSpectrum<T>::AudioSpectrum()
{
    this->channelDataSize = 0;
    this->channelsCount = 0;
    this->windowSize = 0;
}

template <class T>
AudioSpectrum<T>::AudioSpectrum(const AudioSpectrum<T> &spectrum){
    this->setData(spectrum.getData());
    this->frequencyStep = spectrum.frequencyStep;
    this->sampleRate = spectrum.sampleRate;
    this->windowSize = spectrum.windowSize;
}

template <class T>
bool AudioSpectrum<T>::updateFrequencyStep(){
    this->frequencyStep = this->sampleRate/(this->windowSize);
    return true;
}

template <class T>
double AudioSpectrum<T>::getFrequency(int n){
    return this->frequencyStep * n;
}

template <class T>
bool AudioSpectrum<T>::setDataSize(int channels_count, int data_size){
    if(!this->AudioData< std::vector<T> >::setDataSize(channels_count,data_size)) return false;
    return true;
}

template <class T>
bool AudioSpectrum<T>::setSampleRate(int sample_rate){
    this->sampleRate = sample_rate;
    this->updateFrequencyStep();
    return true;
}

template <class T>
bool AudioSpectrum<T>::setWindowSize(int windows_size){
    this->windowSize = windows_size;
    this->updateFrequencyStep();
    return true;
}

#endif // AUDIOSPECTRUM_H
