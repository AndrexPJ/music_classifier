#include "audiorecord.h"

AudioRecord::AudioRecord() : AudioData<double>(){
    this->bitsPerSample = 0;
    this->channelDataSize = 0;
    this->channelsCount = 0;
    this->sampleRate = 0;
}

AudioRecord::AudioRecord(const AudioRecord &record) : AudioData<double>(record.getData()){
    this->bitsPerSample = record.bitsPerSample;
    this->channelDataSize = record.getChannelDataSize();
    this->channelsCount = record.getChannelsCount();
    this->sampleRate = record.getSampleRate();
}

AudioRecord::AudioRecord(AudioData<double> &data, int bitsPerSample) :  AudioData<double>(data.getData()){
    this->bitsPerSample = bitsPerSample;
    this->channelDataSize = data.getChannelDataSize();
    this->channelsCount = data.getChannelsCount();
    this->sampleRate = data.getSampleRate();
}

int AudioRecord::getBitsPerSample() const{
    return this->bitsPerSample;
}

bool AudioRecord::setBitsPerSample(int bps){
    this->bitsPerSample = bps;
    return true;
}


