#include "audiorhythmdescriptors.h"

BeatHistogramDescriptorExtractor::BeatHistogramDescriptorExtractor(CorrelationFunction &c_func, int sample_rate) : AudioDescriptorExtractor(){
    std::vector<double> temp = c_func.getValues();
    int temp_size = temp.size();
    int data_size = temp_size /2;

    this->koeff = 60.0 * sample_rate;

    this->histogram.resize(temp_size - 1);
    this->histogram_size = this->histogram.size();

    for(int i = 2; i < data_size ; i++){
        if(i > this->koeff/50) break;
        if(i < this->koeff/240) continue;
        this->histogram[i-2] = temp[data_size - i + 1];
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

    //result.push_back(sum) ; // +
    //result.push_back(first_peak_amp);
    //result.push_back(second_peak_amp);
    //result.push_back(second_peak_amp / first_peak_amp);
    //result.push_back(double(abs(first_peak_n - second_peak_n)) );
    result.push_back(this->koeff / first_peak_n);
    result.push_back(this->koeff / second_peak_n);
    return result;

}
