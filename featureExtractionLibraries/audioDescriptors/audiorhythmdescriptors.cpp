#include "audiorhythmdescriptors.h"

BeatHistogramDescriptorExtractor::BeatHistogramDescriptorExtractor(CorrelationFunction &c_func, double koeff,int ticks_count) : MainTicksDescriptorExtractor(ticks_count,false){
    std::vector<double> temp = c_func.getValues();
    std::vector<double> temp_histo;
     std::vector<double> result_histo;
    int temp_size = temp.size();
    int data_size = temp_size /2;
    int histo_size = 20;

    this->max_bmp = 240;
    this->min_bmp = 30;

    this->koeff = koeff;

    result_histo.assign(histo_size,0.0);

    for(int i = 0; i < data_size ; i++){
        if(i > this->koeff/this->min_bmp) break;
        if(i < this->koeff/this->max_bmp) continue;
        temp_histo.push_back(temp[i]);
    }

    int temp_histo_size = temp_histo.size();
    double index_koeff = double(histo_size) / temp_histo_size;
    for(int i = 0; i < temp_histo_size;i++){
        result_histo[i * index_koeff] += temp_histo[i];
    }

    this->setHistogram(result_histo);

}

std::vector<double> BeatHistogramDescriptorExtractor::extract(){
   //std::vector<double> result =  this->histogram;

   //for(int i = 0; i < this->ticks_count; i++)
    //   result[i] = getTempID((koeff / (result[i] * this->histogram.size())));

   //std::sort(result.begin(),result.end());

   double max = *std::max_element(this->histogram.begin(), this->histogram.end());

   for(std::vector<double>::iterator it = this->histogram.begin(); it != this->histogram.end(); it++)
       (*it) /= max;

   return this->histogram;
}

double BeatHistogramDescriptorExtractor::getTempID(double bmp){
    if(bmp < 52) return 0.1; // largo
    if(bmp < 58) return 0.2; // lento
    if(bmp < 72) return 0.3; // andante
    if(bmp < 88) return 0.4; // andantino
    if(bmp < 104) return 0.5; // allegretto
    if(bmp < 120) return 0.6; // animato
    if(bmp < 144) return 0.7; // allegro
    if(bmp < 168) return 0.8; // allegro assai
    if(bmp < 192) return 0.9; // vivo
    return 1.0; // prestissimo
}

AudioDescriptorExtractor* BeatHistogramDescriptorExtractor::clone() const{
    return new BeatHistogramDescriptorExtractor(*this);
}
