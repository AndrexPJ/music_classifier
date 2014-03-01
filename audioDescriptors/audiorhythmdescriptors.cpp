#include "audiorhythmdescriptors.h"

BeatHistogramDescriptorExtractor::BeatHistogramDescriptorExtractor(CorrelationFunction &c_func) : AudioDescriptorExtractor(){
    std::vector<double> temp = c_func.getValues();
    int temp_size = temp.size();

    this->histogram.resize(temp_size - 2);
    this->histogram_size = this->histogram.size();

    for(int i = 2; i < temp_size / 2; i++){
        this->histogram[i-2] = temp[i];
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

    result.push_back(sum / this->histogram_size); // +
    //result.push_back(first_peak_amp);
    //result.push_back(second_peak_amp);
    //result.push_back(second_peak_amp / first_peak_amp);
    //result.push_back(double(abs(first_peak_n - second_peak_n)) / this->histogram_size);
    //result.push_back(double(first_peak_n) / this->histogram_size);
    //result.push_back(double(second_peak_n) / this->histogram_size);
    return result;

}
