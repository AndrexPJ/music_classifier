#include "audiowavelettransforms.h"


bool AudioWaveletImageTransforms::performFullWaveRectification(AudioWaveletImage &image){
    for(int ch = 0; ch < image.getChannelsCount(); ch++)
        for(int lvl = 0; lvl < image.getLevelsCount(); lvl++)
            for(int i = 0; i < image.getLevelSize(lvl); i++)
                image.set(ch,lvl,i,fabs(image.get(ch,lvl,i)));
    return true;
}

bool AudioWaveletImageTransforms::performLowPassFiltering(AudioWaveletImage &image, double alpha){
    double temp;

    AudioWaveletImage temp_i = image;
    for(int ch = 0; ch < image.getChannelsCount(); ch++)
        for(int lvl = 0; lvl < image.getLevelsCount(); lvl++){
            image.set(ch,lvl,0,temp_i.get(ch,lvl,0));
            for(int i = 1; i < image.getLevelSize(lvl); i++){
                temp = alpha * temp_i.get(ch,lvl,i) + (1 - alpha) * image.get(ch,lvl,i - 1);
                image.set(ch,lvl,i,temp);
            }
        }
    return true;
}

bool AudioWaveletImageTransforms::performNoiseRemoval(AudioWaveletImage &image){
    double temp;
    for(int ch = 0; ch < image.getChannelsCount(); ch++)
        for(int lvl = 0; lvl < image.getLevelsCount(); lvl++){
            temp = 0.0;
            for(int i = 0; i < image.getLevelSize(lvl); i++)
                temp += image.getGlobal(ch,lvl,i);
            temp /= image.getLevelSize(lvl);

            for(int i = 0; i < image.getLevelSize(lvl); i++)
                image.set(ch,lvl,i, image.get(ch,lvl,i)/temp);
        }
    return true;
}

AudioData<double> AudioWaveletImageTransforms::performSummation(AudioWaveletImage &image, int down_sampling_koeff){
    if(down_sampling_koeff <= 0) down_sampling_koeff = 1;

    int channels_count = image.getChannelsCount();
    int data_size = image.getChannelDataSize() / down_sampling_koeff;

    AudioData<double> result;

    std::vector< std::vector<double> > temp(channels_count);
    for(int ch = 0; ch < channels_count; ch++){
        temp[ch].assign(data_size,0.0);
        for(int i = 0; i < data_size; i++)
            for(int lvl = 0; lvl < image.getLevelsCount(); lvl++)
                temp[ch][i] += image.getGlobal(ch,lvl,down_sampling_koeff * i);
    }

    double norm;
    for(int ch = 0; ch < channels_count; ch++){
        norm = *(std::max_element(temp[ch].begin(),temp[ch].end()));

        for(int i = 0; i < data_size; i++)
            temp[ch][i] /= norm;
    }

    result.setData(temp);
    result.setSampleRate(image.getSampleRate() /down_sampling_koeff);

    return result;
}
