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

int AudioSpectrumTransforms::getCriticalBandRate(double frequency){
    double result = 26.81/(1 + 1960/frequency) - 0.53;
    if(result < 2.0) result += 0.15*(2 - result);
    if(result > 20.1) result += 0.22*(result - 20.1);
    return result;
}
