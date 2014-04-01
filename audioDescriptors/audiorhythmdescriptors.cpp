#include "audiorhythmdescriptors.h"

BeatHistogramDescriptorExtractor::BeatHistogramDescriptorExtractor(CorrelationFunction &c_func, double koeff,int ticks_count) : MainTicksDescriptorExtractor(ticks_count,false){
    std::vector<double> temp = c_func.getValues();
    std::vector<double> temp_histo;
    int temp_size = temp.size();
    int data_size = temp_size /2;

    this->max_bmp = 240;
    this->min_bmp = 30;

    this->koeff = koeff;

    temp_histo.assign(temp_size,0.0);

    for(int i = 0; i < data_size ; i++){
        if(i > this->koeff/this->min_bmp) break;
        if(i < this->koeff/this->max_bmp) continue;
        temp_histo[i] = temp[i];
    }
    this->setHistogram(temp_histo);
    this->fillResult();
}

<<<<<<< HEAD
bool BeatHistogramDescriptorExtractor::fillResult(){
    if(!this->MainTicksDescriptorExtractor::fillResult()) return false;

    int result_size = this->output_result.size();
    for(int i = 0; i < this->ticks_count; i++)
        this->output_result[i] = (koeff / (this->output_result[i] * this->histogram.size())) / this->max_bmp;

    //std::sort(result.begin(),result.end());
    return true;
=======
std::vector<double> BeatHistogramDescriptorExtractor::extract(){
   std::vector<double> result =  this->MainTicksDescriptorExtractor::extract();

   for(int i = 0; i < this->ticks_count; i++)
       result[i] = (koeff / (result[i] * this->histogram.size())) / this->max_bmp;

   return result;
>>>>>>> not-tested
}

