#include <iostream>
#include "audioLoaders/waveaudioloader.h"
#include "audioTransforms/audiowfft.h"
#include "audioTransforms/audiorecordtransforms.h"
#include "audioTransforms/audiospectrumtransforms.h"
#include "audioDescriptors/audiodescriptorextractor.h"
#include "audioDescriptors/audiodescriptors.h"

#include <fstream>


using namespace std;

int main(int argc, char *argv[])
{
    AudioRecord ar =  WaveAudioLoader::loadAudioRecord("test.wav");

    int window_size = 2048;
    int hop_size = window_size * 0.5; // 2048 window_size and hop_size = 0.5 * window_size is a best for audio analysing
    HanningWindowFunction wf(window_size);


    AudioSpectrum<complex> sp;
    sp.setWindowSize(window_size);


    AudioWFFT::perform(ar,sp,wf,window_size,hop_size);


    AudioAmpSpectrum amp_sp = AudioSpectrumTransforms::getAmpSpectrum(sp);

    EnergyDescriptorExtractor energy_de(ar);
    ZCRDescriptorExtractor zcr_de(ar);
    SpCentroidDescriptorExtractor spc_de(amp_sp);

    std::vector<double> out = energy_de.extract();
    for(int i = 0; i < out.size(); i++){
        cout << out[i] << " ";
    }

    out = zcr_de.extract();
    for(int i = 0; i < out.size(); i++){
        cout << out[i] << " ";
    }


    out = spc_de.extract();
    for(int i = 0; i < out.size(); i++){
        cout << out[i] << endl;
    }

    /*ofstream out_stream;
    out_stream.open("out.txt",ios_base::out);


    for(int i = 0; i < amp_sp.channelDataSize;i++){
        for(int j = 0; j < window_size/2; j++){
            out_stream << amp_sp.getFrequency(j) << " " << 10*log(amp_sp[0][i][j]) << endl;
        }
    }

    for(int i = 0; i< ar.channelDataSize; i++)
        out_stream << ar[0][i] << endl;*/

    //out_stream.close();

    //TODO : fix problem with spectrum size
    return 0;
}

