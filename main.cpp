#include <iostream>
#include "audioLoaders/waveaudioloader.h"
#include "audioTransforms/audiowfft.h"
#include "audioTransforms/audiorecordtransforms.h"
#include <fstream>


using namespace std;

int main()
{
    AudioRecord ar =  WaveAudioLoader::loadAudioRecord("country.wav");

    int prefix_size,suffix_size;

    ar = AudioRecordTransforms::SizingToPowerOfTwo::perform(ar,prefix_size,suffix_size);

    AudioSpectrum<complex> sp;
    cout << AudioWFFT::perform(ar,sp,1024) << endl;


    ofstream out_stream;
    out_stream.open("out1.txt",ios_base::out);

    cout << sp.channelDataSize << endl;

    for(int i = 0; i < sp.channelDataSize; i++)
        out_stream << sqrt(pow(sp[0][i].re(),2) + pow(sp[0][i].im(),2)) << " " << sp.getFrequency(i) << endl;
        //out_stream << atan(result[i].re()/result[i].im()) << endl;
        //out_stream << ar[0][i] << endl;


    //TODO: frequency step update !!!!!!
    return 0;
}

