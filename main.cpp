#include <iostream>
#include "audioLoaders/waveaudioloader.h"
#include "audioTransforms/audiowfft.h"
#include "audioTransforms/audiorecordtransforms.h"
#include "audioTransforms/audiospectrumtransforms.h"

#include <fstream>


using namespace std;

int main()
{
    AudioRecord ar =  WaveAudioLoader::loadAudioRecord("country.wav");


    int window_size = 2048;
    int hop_size = window_size * 0.5; // 2048 window_size and hop_size = 0.5 * window_size is a best for audio analysing
    HannWindowFunction wf;


    AudioSpectrum<complex> sp;
    sp.setWindowSize(window_size);


    AudioWFFT::perform(ar,sp,wf,window_size,hop_size);
    AudioAmpSpectrum amp_sp = AudioSpectrumTransforms::getAmpSpectrum(sp);


    ofstream out_stream;
    out_stream.open("out.txt",ios_base::out);


    for(int i = 0; i < amp_sp.channelDataSize;i++){
        for(int j = 0; j < window_size/2; j++){
            out_stream << amp_sp.getFrequency(j) << " " << 10*log(amp_sp[0][i][j]/amp_sp[0][i][0]) << endl;
        }
    }

    out_stream.close();
    return 0;
}

