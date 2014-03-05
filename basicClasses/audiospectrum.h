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
protected:
    double frequencyStep;
    int windowSize;
public:
    AudioSpectrum();
    AudioSpectrum(const AudioSpectrum<T> &spectrum);
    double getFrequency(int n) const;
    bool setDataSize(int channels_count, int data_size, int window_size);
    bool setSampleRate(int sample_rate);
    bool setWindowSize(int windows_size);

    double getFrequencyStep() const;
    bool setFrequencyStep(double step);

    int getFrequencyCount() const;
    int getWindowSize() const;

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
    if(this->windowSize == 0) return false;
    this->frequencyStep = double(this->sampleRate)/(this->windowSize);
    return true;
}

template <class T>
double AudioSpectrum<T>::getFrequency(int n) const{
    return this->frequencyStep * n;
}

template <class T>
bool AudioSpectrum<T>::setDataSize(int channels_count, int data_size, int window_size){
    if(!this->AudioData< std::vector<T> >::setDataSize(channels_count,data_size)) return false;
    for(int i = 0; i < channels_count; i++)
        for(int j = 0; j < data_size; j++)
            this->channelsData[i][j].resize(window_size);
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

template <class T>
double AudioSpectrum<T>::getFrequencyStep() const{
    return this->frequencyStep;
}

template <class T>
bool AudioSpectrum<T>::setFrequencyStep(double step){
    this->frequencyStep = step;
    return true;
}

template <class T>
int AudioSpectrum<T>::getFrequencyCount() const{
    return this->getWindowSize()/2;
}

template <class T>
int AudioSpectrum<T>::getWindowSize() const{
    return this->windowSize;
}

#endif // AUDIOSPECTRUM_H
