#include "audiorhythmdescriptors.h"

BeatHistogramDescriptorExtractor::BeatHistogramDescriptorExtractor(CorrelationFunction &c_func, double koeff) : AudioDescriptorExtractor(){
    std::vector<double> temp = c_func.getValues();
    int temp_size = temp.size();
    int data_size = temp_size /2;

    this->max_bmp = 240;
    this->min_bmp = 50;

    this->koeff = koeff;

    this->histogram.assign(temp_size,0.0);
    this->histogram_size = this->histogram.size();

    for(int i = 0; i < data_size ; i++){
        if(i > this->koeff/this->min_bmp) break;
        if(i < this->koeff/this->max_bmp) continue;
        this->histogram[i] = temp[i];
    }

}

std::vector<double> BeatHistogramDescriptorExtractor::extract(){
    std::vector<double> result;

    double sum = 0.0;
    double first_peak_amp, second_peak_amp;
    int first_peak_n, second_peak_n;

    first_peak_amp = this->histogram[0];
    first_peak_n = 0;

    second_peak_amp = this->histogram[0];
    second_peak_n = 0;

    sum += first_peak_amp;
    for(int i = 1; i < this->histogram_size; i++){
        sum += this->histogram[i];
        if(this->histogram[i] > first_peak_amp){
            second_peak_amp = first_peak_amp;
            second_peak_n = first_peak_n;

            first_peak_amp = this->histogram[i];
            first_peak_n = i;
        }
        else{
            if(this->histogram[i] > second_peak_amp){
                second_peak_amp = this->histogram[i];
                second_peak_n = i;
            }
        }
    }


    double first = this->koeff / first_peak_n;
    double second = this->koeff / second_peak_n;
    //result.push_back(first_peak_amp);
    //result.push_back(second_peak_amp);
    result.push_back(first);
    result.push_back(first_peak_amp);
    result.push_back(second);
    result.push_back(second_peak_amp);
    result.push_back(second / first);
    return result;

}
