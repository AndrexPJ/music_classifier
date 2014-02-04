#include "audiorecord.h"

AudioRecord::AudioRecord() : AudioData(){
    this->bitsPerSample = 0;
    this->channelDataSize = 0;
    this->channelsCount = 0;
    this->sampleRate = 0;
}

AudioRecord::AudioRecord(const AudioRecord &record){
    this->bitsPerSample = record.bitsPerSample;
    this->channelDataSize = record.channelDataSize;
    this->channelsCount = record.channelsCount;
    this->sampleRate = record.sampleRate;
    this->setData(record.getData());
}
