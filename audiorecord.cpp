#include "audiorecord.h"

AudioRecord::AudioRecord(){
}

AudioRecord::AudioRecord(const AudioRecord &record){
    this->bitsPerSample = record.bitsPerSample;
    this->channelDataSize = record.channelDataSize;
    this->channelsCount = record.channelsCount;
    this->sampleRate = record.sampleRate;

    this->channelsData = std::vector< std::vector <double> >(record.channelsData);
}
