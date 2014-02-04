#include "audiodata.h"

AudioData::AudioData(){
    this->channelsData.resize(0);
}

AudioData::~AudioData(){
    this->channelsData.clear();
}

bool AudioData::setData(std::vector<std::vector<double> > const &data){
    this->channelsData = std::vector< std::vector<double> >(data);
    return true;
}

std::vector<std::vector<double> > AudioData::getData() const{
    return this->channelsData;
}


bool AudioData::setSpecificData(double data,int channel, int n){

    if(checkDataAvailability(channel,n)){
        this->channelsData[channel][n] = data;
        return true;
    }
    else{
        return false;
    }

}

bool AudioData::getSpecificData(double &out_data, int channel, int n) const{
    if(checkDataAvailability(channel,n)){
        out_data =  this->channelsData[channel][n];
        return true;
    }
    else{
        return false;
    }
}

bool AudioData::checkDataAvailability(int channel, int n) const{
    int channel_size = this->channelsData.size();
    if(channel_size == 0) return false;
    if((channel > channel_size - 1) || (channel < 0)) return false;

    int data_size = this->channelsData[channel_size - 1].size();
    if((n > data_size - 1) || (n < 0 )) return false;

    return true;

}


bool AudioData::setDataSize(int channels_count){
    if(channels_count < 0) return false;
    this->channelsData.resize(channels_count);

    return true;
}

bool AudioData::setDataSize(int channels_count, int data_size){
    if(this->setDataSize(channels_count)){
        if(data_size < 0) return false;

        for(int i = 0; i < channels_count; i++)
            this->channelsData[i].resize(data_size);

        return true;
    }
    else return false;

}
