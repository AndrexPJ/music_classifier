#include "audiorecordtransforms.h"

AudioRecord AudioRecordTransforms::sizeToPowerOfTwo(const AudioRecord &record, int &out_prefix_size, int &out_suffix_size){
    int old_size = record.getChannelDataSize();

    if((old_size & (old_size - 1)) == 0){ // if old_size is power of two!
        out_prefix_size = 0;
        out_suffix_size = 0;
        return record;
    }
    int new_size = Tools::nearestPowerOfTwoAbove(old_size);


    int prefix_size = (new_size - old_size)/2;
    int suffix_size = (new_size - old_size) - prefix_size;

    std::vector< std::vector<double> > temp;

    std::vector< std::vector<double> > record_data = record.getData();

    temp.resize(record.getChannelsCount());

    for(int i= 0; i < record.getChannelsCount(); i++)
        temp[i].reserve(new_size);

    for(int i = 0; i < record.getChannelsCount(); i++)
    for(int j = 0; j < prefix_size; j++)
        temp[i].push_back(0);

    for(int i = 0; i < record.getChannelsCount(); i++)
        temp[i].insert(temp[i].end(),record_data[i].begin(),record_data[i].end());

    for(int i = 0; i < record.getChannelsCount(); i++)
    for(int j = 0; j < suffix_size; j++)
        temp[i].push_back(0);


    AudioRecord temp_record;
    temp_record.setBitsPerSample(record.getBitsPerSample());
    temp_record.setDataSize(record.getChannelsCount(), temp[0].size());
    temp_record.setData(temp);
    temp_record.setSampleRate(record.getSampleRate());

    out_prefix_size = prefix_size;
    out_suffix_size = suffix_size;

    return temp_record;
}


AudioRecord AudioRecordTransforms::performPreEmphasisFilter(const AudioRecord &record, double koefficient){
    AudioRecord temp_record(record);
    std::vector< std::vector<double> > temp;
    temp.resize(temp_record.getChannelsCount());
    for(int i = 0; i < temp_record.getChannelsCount(); i++)
        temp[i].resize(temp_record.getChannelDataSize());

    for(int i = 0; i < temp_record.getChannelsCount(); i++){
        for(int j = 1; j < temp_record.getChannelDataSize(); j++)
            temp[i][j] = temp_record[i][j] - koefficient * temp_record[i][j - 1];
    }

    temp_record.setData(temp);
    return temp_record;

}
