#include "audiotonalitydescriptors.h"

MainPitchesDescriptorExtractor::MainPitchesDescriptorExtractor(AudioPitchChroma &pitch_chroma, int pitches_count) : MainTicksDescriptorExtractor(pitch_chroma,pitches_count){
}

std::vector<double> MainPitchesDescriptorExtractor::extract(){
    return this->MainTicksDescriptorExtractor::extract();
}

AudioDescriptorExtractor* MainPitchesDescriptorExtractor::clone(){
    return new MainPitchesDescriptorExtractor(*this);
}
