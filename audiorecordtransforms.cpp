#include "audiorecordtransforms.h"

using namespace AudioRecordTransforms;

AudioRecord sizingToPowerOfTwo::perform(const AudioRecord &record){
    int old_size = record.channelDataSize;

    if((old_size & (old_size - 1)) == 0) return record; // if old_size is power of two!

    int new_size = nearestPowerOfTwoAbove(old_size);


    int prefix_size = (new_size - old_size)/2;
    int suffix_size = (new_size - old_size) - prefix_size;


    std::vector< std::vector<double> > temp;
    temp.resize(record.channelsCount);

    for(int i= 0; i < record.channelsCount; i++)
        temp[i].reserve(new_size);

    for(int i = 0; i < record.channelsCount; i++)
    for(int j = 0; j < prefix_size; j++)
        temp[i].push_back(0);

    for(int i = 0; i < record.channelsCount; i++)
        temp[i].insert(temp[i].end(),record.channelsData[i].begin(),record.channelsData[i].end());

    for(int i = 0; i < record.channelsCount; i++)
    for(int j = 0; j < suffix_size; j++)
        temp[i].push_back(0);


    AudioRecord temp_record;
    temp_record.bitsPerSample = record.bitsPerSample;
    temp_record.channelDataSize = temp[0].size();
    temp_record.channelsCount = record.channelsCount;
    temp_record.channelsData = temp;
    temp_record.sampleRate = record.sampleRate;



    return temp_record;
}
