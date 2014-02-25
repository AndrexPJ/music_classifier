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
