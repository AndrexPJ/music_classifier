#include "audiodata.h"

AudioHistogram::AudioHistogram(AudioData<double> &data) : AudioData<double>(data){
    double norm;

    for(int ch = 0; ch < this->getChannelsCount(); ch++){
        norm = 0.0;
        for(int i = 0; i < this->getChannelDataSize(); i++)
            norm += this->channelsData[ch][i];
        for(int i = 0; i < this->getChannelDataSize(); i++)
            this->channelsData[ch][i] /= norm;
    }


}

