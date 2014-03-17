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
                temp[i][j][k] =  spectrum[i][j][k].norm();
            }
        }
    }

    temp.setWindowSize(spectrum.getWindowSize());
    temp.setFrequencyStep(spectrum.getFrequencyStep());
    temp.setSampleRate(spectrum.getSampleRate());

    return temp;

}

AudioPhaseSpectrum AudioSpectrumTransforms::getPhaseSpectrum(AudioSpectrum<complex> &spectrum){
    AudioPhaseSpectrum temp;


    int half_window = spectrum.getFrequencyCount(); // frequency count is half window size
    int channels_count = spectrum.getChannelsCount();
    int data_size = spectrum.getChannelDataSize();

    double epsilon = std::numeric_limits<double>::epsilon();

    temp.setDataSize(channels_count,data_size, half_window);

    for(int i = 0; i < channels_count; i++){
        for(int j = 0; j < data_size; j++){
            for(int k = 0; k < half_window; k++){
                if(spectrum[i][j][k].re() <= epsilon)
                    temp[i][j][k] = M_PI/2;
                else
                    temp[i][j][k] =  atan((-spectrum[i][j][k].im())/spectrum[i][j][k].re());
            }
        }
    }

    temp.setWindowSize(spectrum.getWindowSize());
    temp.setFrequencyStep(spectrum.getFrequencyStep());
    temp.setSampleRate(spectrum.getSampleRate());

    return temp;

}

AudioAmpSpectrum AudioSpectrumTransforms::getLogAmpSpectrum(AudioAmpSpectrum &spectrum){
     AudioAmpSpectrum temp;
     int fq_count = spectrum.getFrequencyCount();
     int channels_count = spectrum.getChannelsCount();
     int data_size = spectrum.getChannelDataSize();

     double epsilon = std::numeric_limits<double>::epsilon();

     temp.setDataSize(channels_count,data_size, fq_count);

     for(int i = 0; i < channels_count; i++){
         for(int j = 0; j < data_size; j++){
             for(int k = 0; k < fq_count; k++){
                 if(spectrum[i][j][k] <= epsilon)
                     temp[i][j][k] = 0;
                 else
                     temp[i][j][k] =  10 *log10(spectrum[i][j][k]);
             }
         }
     }

     temp.setWindowSize(spectrum.getWindowSize());
     temp.setFrequencyStep(spectrum.getFrequencyStep());
     temp.setSampleRate(spectrum.getSampleRate());

     return temp;

}

AudioPitchChroma AudioSpectrumTransforms::getPitchChroma(AudioAmpSpectrum &spectrum){
    AudioPitchChroma temp;

    int filters_count = 12;

    double norm;
    int frequency_count = spectrum.getFrequencyCount();
    int data_size = spectrum.getChannelDataSize();
    int channels_count = spectrum.getChannelsCount();

    std::vector< std::vector<double> > filters = AudioSpectrumTools::getSemiToneFilterbank(frequency_count,spectrum.getFrequency(frequency_count - 1));

    std::vector<std::vector<std::vector<double> > > result(channels_count);

    for(int ch = 0; ch < channels_count; ch++){
        result[ch].resize(data_size);

        for(int i = 0; i < data_size; i++){
            norm = 0.0;
            result[ch][i].assign(filters_count,0.0);

            for(int filt_i = 0; filt_i < filters_count; filt_i++){
                for(int fq_i = 0; fq_i < frequency_count; fq_i++)
                    result[ch][i][filt_i] += spectrum[ch][i][fq_i] * spectrum[ch][i][fq_i] * filters[filt_i][fq_i];
                norm += result[ch][i][filt_i];
            }


            for(int filt_i = 0; filt_i < filters_count; filt_i++)
                result[ch][i][filt_i] /= norm;

        }
    }

    temp.setData(result);
    temp.setSampleRate(spectrum.getSampleRate());
    temp.setWindowSize(24);

    return temp;

}

AudioBeatSpectrum AudioSpectrumTransforms::getBeatSpectrum(AudioAmpSpectrum &spectrum){
    AudioBeatSpectrum temp;
    std::vector< std::vector<std::vector<double> > > temp_vector;
    std::vector<double> temp_ac_vector;

    int channels_count = spectrum.getChannelsCount();
    int N = spectrum.getChannelDataSize();
    temp_vector.resize(channels_count);
    temp_ac_vector.resize(N);

    AutocorrelationFunction ac_f;

    for(int ch = 0; ch < channels_count; ch++)
    {
        temp_vector[ch] = Tools::getSimilarityMatrix(spectrum[ch]);
        /*for(int i = 0; i < N; i++){
            ac_f = AutocorrelationFunction(temp_vector[ch][i]);
            temp_vector[ch][i] = ac_f.getValues();
        }*/
    }

    temp.setData(temp_vector);
    temp.setWindowSize(2 * N);
    temp.setSampleRate(2 * N);


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


std::vector< std::vector<double> > AudioSpectrumTools::getSemiToneFilterbank(int frequency_count, double max_frequency , double mid_frequency, int octaves_count){
    int filters_count = 12;


    double first_bound_base = pow(2,-1.0/24) * frequency_count / max_frequency ; //0.971532;
    double second_bound_base = pow(2,1.0/24) * frequency_count / max_frequency ; //1.0293;
    double bound_step = pow(2,1.0/12);// 1.05946;

    double peak = 0.0;
    int power_of_two;
    int center;

    int first_bound_i, second_bound_i;
    double first_bound, second_bound;

    while(mid_frequency * (2 << (octaves_count - 1)) > frequency_count)
        octaves_count--;

    std::vector< std::vector<double> > result_filters(filters_count);

    for(int filt_i = 0; filt_i < filters_count; filt_i++){
        result_filters[filt_i].assign(frequency_count,0.0);

        first_bound = first_bound_base * mid_frequency;
        second_bound = second_bound_base * mid_frequency;

        power_of_two = 1;

        for(int octv_i = 0; octv_i < octaves_count; octv_i++){
            first_bound_i = ceil(power_of_two * first_bound );
            second_bound_i = floor(power_of_two * second_bound );

            power_of_two <<= 1;

            peak = 1.0 / (second_bound_i + 1 - first_bound_i);
            center = (first_bound_i + second_bound_i) / 2;

            for(int i = first_bound_i; i <= second_bound_i; i++)
                result_filters[filt_i][i] = peak;

        }

        mid_frequency *= bound_step;

    }

    return result_filters;
}


