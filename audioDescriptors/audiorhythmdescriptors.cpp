#include "audiorhythmdescriptors.h"


AutocorrelationFunction::AutocorrelationFunction(std::vector<double> in_values){
    std::vector<complex> temp;
    std::vector<complex> result;

    int N = in_values.size();
    int suffix_size = 0;

    if(N & (N - 1)){
        int new_N = Tools::nearestPowerOfTwoAbove(N);

        suffix_size = new_N - N;

        for(int i = 0; i < suffix_size; i++)
            in_values.push_back(0);
        N = new_N;
    }

    FFT::Forward(in_values, temp);

    for(int i = 0; i < N; i++)
        temp[i] *= temp[i];

    FFT::Inverse(temp,result);

    this->values.resize(N-suffix_size);
    this->interval_size = N - suffix_size;

    for(int i = 0; i < N - suffix_size; i++)
        this->values[i] = sqrt(pow(result[i].im(),2) + pow(result[i].re(),2));
}


double AutocorrelationFunction::perform(int n){
     if(n < 0 || n >= this->interval_size) return 0.0;
     else return this->values[n];
}

int AutocorrelationFunction::getIntervalSize() const{
    return this->interval_size;
}

std::vector<double> AutocorrelationFunction::getValues() const{
    return this->values;
}


BeatHistogramDescriptorExtractor::BeatHistogramDescriptorExtractor(AutocorrelationFunction &ac_func) : AudioDescriptorExtractor(){
    std::vector<double> temp = ac_func.getValues();
    int temp_size = temp.size();

    this->histogram.resize(temp_size - 2);
    this->histogram_size = this->histogram.size();

    for(int i = 2; i < temp_size; i++){
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

    //result.push_back(sum);
    //result.push_back(first_peak_amp);
    //result.push_back(second_peak_amp);
    result.push_back(second_peak_amp / first_peak_amp);
    result.push_back(double(abs(first_peak_n - second_peak_n)) / this->histogram_size);
    //result.push_back(double(second_peak_n) / this->histogram_size);
    return result;

}
