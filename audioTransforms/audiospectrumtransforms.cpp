#include "audioTransforms/audiospectrumtransforms.h"


AudioAmpSpectrum AudioSpectrumTransforms::getAmpSpectrum(AudioSpectrum<complex> &spectrum){
    AudioAmpSpectrum temp;


    int half_window = spectrum.getFrequencyCount(); // frequency count is half window size
    int channels_count = spectrum.getChannelsCount();
    int data_size = spectrum.getChannelDataSize();

    temp.setDataSize(channels_count,data_size, half_window);

    for(int i = 0; i < channels_count; i++){
        for(int j = 0; j < data_size; j++){
            for(int k = 0; k < half_window; k++){
                temp[i][j][k] =  sqrt(pow(spectrum[i][j][k].im(),2) + pow(spectrum[i][j][k].re(),2));
            }
        }
    }

    temp.setWindowSize(spectrum.getWindowSize());
    temp.setFrequencyStep(spectrum.getFrequencyStep());
    temp.setSampleRate(spectrum.getSampleRate());

    return temp;

}

int AudioSpectrumTools::getCriticalBandRate(double frequency){
    double result = 26.81/(1 + 1960/frequency) - 0.53;
    if(result < 2.0) result += 0.15*(2 - result);
    if(result > 20.1) result += 0.22*(result - 20.1);
    return result;
}


double AudioSpectrumTools::frequencyToMel(double frequency){
    return 1125 * log(1 + (frequency / 700));
}

double AudioSpectrumTools::melToFrequency(double mel){
    return 700 * (exp(mel / 1125) - 1);
}

std::vector< std::vector<double> > AudioSpectrumTools::getMelFilterbank(int frequency_count, double max_frequency, double min_frequency, int filters_count){
    std::vector< std::vector<double> > result_filters;
    result_filters.resize(filters_count);

    double min_mel = AudioSpectrumTools::frequencyToMel(min_frequency);
    double max_mel = AudioSpectrumTools::frequencyToMel(max_frequency);

    int points_count = filters_count + 2;

    double step  = (max_mel - min_mel) / (points_count - 1);

    std::vector<int> frequency_numbers;
    frequency_numbers.resize(points_count);

    for(int i = 0; i < points_count; i++)
        frequency_numbers[i] = (frequency_count * AudioSpectrumTools::melToFrequency(min_mel + i * step) ) / max_frequency;

    double temp;
    for(int i = 0; i < filters_count; i++){
        result_filters[i].resize(frequency_count);
        for(int fq_i = 0; fq_i < frequency_count; fq_i++){
            temp = 0.0;
            if( (fq_i >= frequency_numbers[i]) && (fq_i <= frequency_numbers[i+1]) )
                temp = (double(fq_i - frequency_numbers[i])) / (frequency_numbers[i+1] - frequency_numbers[i]);

            if( (fq_i >= frequency_numbers[i+1]) && (fq_i <= frequency_numbers[i+2]))
                temp = (double(frequency_numbers[i+2] - fq_i)) / (frequency_numbers[i+2] - frequency_numbers[i+1]);

            result_filters[i][fq_i] = temp;
        }

    }

    return result_filters;

}
