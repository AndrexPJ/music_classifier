#include "audiodwt.h"



bool AudioDWT::perform(AudioRecord &record, AudioWaveletImage &result_image){
    int channels_count = record.getChannelsCount();

    std::vector< std::vector<double> > temp;
    temp.resize(channels_count);

    for(int i = 0; i < channels_count; i++){
        if(!DWT::Forward(record[i],temp[i])) return false;
    }

    result_image = AudioWaveletImage(temp);
    result_image.setSampleRate(record.getSampleRate());


    return true;

}
