#include "audiowaveletimage.h"

AudioWaveletImage::AudioWaveletImage()
{
    this->levels_count = 0;
}

AudioWaveletImage::AudioWaveletImage(const std::vector< std::vector<double> > &wavelet_raw_data) {
    this->values = wavelet_raw_data;
    this->channels_count = this->values.size();
    this->levels_count = log2(this->values[this->channels_count - 1].size());
}

bool AudioWaveletImage::checkAvailability(int channel, int level, int number){
    int bound = 2 << (level - 1);
    return (channel < 0 || channel >= this->channels_count || level < 0 || level >= this->levels_count || number < 0 || number >= bound);
}

int AudioWaveletImage::getLevelsCount(){
    return this->levels_count;
}

int AudioWaveletImage::getLevelSize(int level){
    if(level >= 0 && level < this->levels_count){
        return (2 << (level - 1));
    }
    else return -1;
}


double AudioWaveletImage::get(int channel,int level, int number){
    int bound = 2 << (level - 1);
    if (this->checkAvailability(channel,level,number))
        return 0.0;

    return this->values[channel][bound + number];
}

bool AudioWaveletImage::set(int channel, int level, int number, double value){
    int bound = 2 << (level - 1);
    if (this->checkAvailability(channel,level,number))
        return false;

    this->values[channel][bound + number] = value;
    return true;
}
