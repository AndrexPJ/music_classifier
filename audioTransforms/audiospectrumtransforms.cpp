#include "audioTransforms/audiospectrumtransforms.h"


AudioAmpSpectrum AudioSpectrumTransforms::getAmpSpectrum(AudioSpectrum<complex> &spectrum){
    AudioAmpSpectrum temp;
    int half_window = spectrum.windowSize/2; // frequency count is half window size

    temp.setDataSize(spectrum.channelsCount,spectrum.channelDataSize);

    for(int i = 0; i < spectrum.channelsCount; i++){
        for(int j = 0; j < spectrum.channelDataSize; j++){
            temp[i][j].resize(half_window);
            for(int k = 0; k < half_window; k++)
                temp[i][j][k] =  sqrt(pow(spectrum[i][j][k].im(),2) + pow(spectrum[i][j][k].re(),2));
        }
    }

    temp.windowSize = spectrum.windowSize;
    temp.frequencyStep = spectrum.frequencyStep;
    temp.sampleRate = spectrum.sampleRate;

    return temp;

}
