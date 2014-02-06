#include <iostream>
#include "audioLoaders/waveaudioloader.h"
#include "audioTransforms/audiowfft.h"
#include "audioTransforms/audiorecordtransforms.h"
#include <fstream>


using namespace std;

int main()
{
    AudioRecord ar =  WaveAudioLoader::loadAudioRecord("country.wav");

    //int prefix_size,suffix_size;

    //ar = AudioRecordTransforms::SizingToPowerOfTwo::perform(ar,prefix_size,suffix_size);

    AudioSpectrum<complex> sp;


    int hop_size = 1024;
    int window_size = 2048;
    sp.setWindowSize(2048);
    cout << AudioWFFT::perform(ar,sp,window_size,hop_size) << endl; // 2048 window_size and 1024 hop_size is a best for audio analysing


    ofstream out_stream;
    out_stream.open("out.txt",ios_base::out);

    cout << sp.channelDataSize << endl;
    //cout << sp.frequencyStep << endl;

    for(int i = 0; i< sp.channelDataSize; i+= window_size/2){
            for(int j = 0; j<window_size/2; j++)
            out_stream << i+j << " " << sp.getFrequency(j) << " " <<(sqrt(pow(sp[0][i+j].re(),2) + pow(sp[0][i+j].im(),2)))  << endl;

    }

    // TODO : try to understand what result of wfft is
    out_stream.close();
    return 0;
}

