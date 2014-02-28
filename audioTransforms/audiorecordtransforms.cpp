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


AudioRecord AudioRecordTransforms::performHighPassFilter(const AudioRecord &record, double cut_off){

    double RC = 1.0 / (2 * M_PI * cut_off);
    double dt = 1.0 / record.getSampleRate();
    double alpha = RC / (RC + dt);

    AudioRecord temp_record(record);
    std::vector< std::vector<double> > temp;
    temp.resize(temp_record.getChannelsCount());
    for(int i = 0; i < temp_record.getChannelsCount(); i++)
        temp[i].resize(temp_record.getChannelDataSize());

    for(int i = 0; i < temp_record.getChannelsCount(); i++){
        temp[i][0] = temp_record[i][0];
        for(int j = 1; j < temp_record.getChannelDataSize(); j++)
            temp[i][j] = alpha * (temp[i][j-1] + temp_record[i][j] - temp_record[i][j - 1]);
    }

    temp_record.setData(temp);
    return temp_record;
}


AudioRecord AudioRecordTransforms::performLowPassFilter(const AudioRecord &record, double cut_off){

    double RC = 1.0 / (2 * M_PI * cut_off);
    double dt = 1.0 / record.getSampleRate();
    double alpha = dt / (RC + dt);

    AudioRecord temp_record(record);
    std::vector< std::vector<double> > temp;
    temp.resize(temp_record.getChannelsCount());
    for(int i = 0; i < temp_record.getChannelsCount(); i++)
        temp[i].resize(temp_record.getChannelDataSize());

    for(int i = 0; i < temp_record.getChannelsCount(); i++){
        temp[i][0] = temp_record[i][0];
        for(int j = 1; j < temp_record.getChannelDataSize(); j++)
            temp[i][j] = temp[i][j-1] + alpha * (temp_record[i][j] - temp[i][j - 1]);
    }

    temp_record.setData(temp);
    return temp_record;
}

AudioRecord AudioRecordTransforms::performDCRemoval(const AudioRecord &record){
    AudioRecord temp_record(record);

    double a_mean  = 0.0;

    int channels_count = temp_record.getChannelsCount();
    int data_size = temp_record.getChannelDataSize();

    for(int ch = 0; ch < channels_count; ch++){
        a_mean = 0.0;

        for(int i = 0; i < data_size; i++)
            a_mean += temp_record[ch][i];
        a_mean /= data_size;

        for(int i = 0; i < data_size; i++)
            temp_record[ch][i] -= a_mean;
    }

    return temp_record;
}

