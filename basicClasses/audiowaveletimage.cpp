#include "audiowaveletimage.h"

AudioWaveletImage::AudioWaveletImage() : AudioData<double>()
{
    this->levelsCount = 0;
}

AudioWaveletImage::AudioWaveletImage(const std::vector< std::vector<double> > &wavelet_raw_data) : AudioData<double>()
{
    this->setData(wavelet_raw_data);
    this->levelsCount = log2(this->channelsData[this->channelsCount - 1].size());
}

bool AudioWaveletImage::checkAvailability(int channel, int level, int number) const {
    int bound = 1 << level;
    return (channel < 0 || channel >= this->channelsCount || level < 0 || level >= this->levelsCount || number < 0 || number >= bound);
}

int AudioWaveletImage::getLevelsCount() const {
    return this->levelsCount;
}

int AudioWaveletImage::getLevelSize(int level) const {
    if(level >= 0 && level < this->levelsCount){
        return (1 << (level));
    }
    else return -1;
}


double AudioWaveletImage::get(int channel,int number, int level) const {
    int bound = 1 << level;
    if (this->checkAvailability(channel,level,number))
        return 0.0;

    return this->channelsData[channel][bound + number];
}


bool AudioWaveletImage::set(int channel,int number, double value, int level){
    int bound = 1 << level;
    if (this->checkAvailability(channel,level,number))
        return false;

    this->channelsData[channel][bound + number] = value;
    return true;
}

int AudioWaveletImage::getChannelsCount() const{
    return this->channelsCount;
}
