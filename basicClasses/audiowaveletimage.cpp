#include "audiowaveletimage.h"
#include <iostream>
AudioWaveletImage::AudioWaveletImage() : AudioData<double>()
{
    this->levelsCount = 0;

}

AudioWaveletImage::AudioWaveletImage(const std::vector< std::vector<double> > &wavelet_raw_data) : AudioData<double>(wavelet_raw_data)
{
    this->levelsCount = log2(this->channelDataSize);
}

bool AudioWaveletImage::checkAvailability(int channel, int level, int number) const {
    int bound = this->getBound(level);
    return !(channel < 0 || channel >= this->channelsCount || level < 0 || level >= this->levelsCount || number < 0 || number >= bound);
}

int AudioWaveletImage::getLevelsCount() const {
    return this->levelsCount;
}

int AudioWaveletImage::getLevelSize(int level) const {
    if(level >= 0 && level < this->levelsCount){
        return (1 << (level));
    }
    else return 0;
}


double AudioWaveletImage::get(int channel, int level, int number) const {
    int bound = this->getBound(level);
    if (!this->checkAvailability(channel,level,number))
        return 0.0;

    return this->channelsData[channel][bound + number];
}

double AudioWaveletImage::getGlobal(int channel, int level, int number) const{
    int n = this->getLevelSize(level);
    int i = n * (double(number)/ this->channelDataSize);
    return this->get(channel,level,i);
}

bool AudioWaveletImage::set(int channel,int level, int number, double value){
    int bound = this->getBound(level);
    if (!this->checkAvailability(channel,level,number))
        return false;

    this->channelsData[channel][bound + number] = value;
    return true;
}

int AudioWaveletImage::getChannelsCount() const{
    return this->channelsCount;
}

int AudioWaveletImage::getBound(int level) const{
    return (1 << level);
}
