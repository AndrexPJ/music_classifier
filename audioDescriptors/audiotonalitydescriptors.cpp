#include "audiotonalitydescriptors.h"

MainPitchDescriptorExtractor::MainPitchDescriptorExtractor(AudioPitchChroma &pitch_chroma, int pitches_count) : HistogramDescriptorExtractor(pitch_chroma){
this->pitches_count = pitches_count;
}

std::vector<double> MainPitchDescriptorExtractor::extract(){
    int result_size = this->pitches_count * 2;

    std::vector<double> temp = this->HistogramDescriptorExtractor::extract();
    std::vector<double> temp2 = temp;
    std::vector<double> result(result_size);

    std::sort(temp2.begin(),temp2.end());
    std::reverse(temp2.begin(),temp2.end());

    for(int i = 0; i < this->pitches_count; i++){
        result[i] = temp2[i];
        result[i+this->pitches_count] = double(std::find(temp.begin(),temp.end(),temp2[i]) - temp.begin()) / (temp.size() - 1);
    }

    return result;

}
