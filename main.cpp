#include <iostream>
#include "audioLoaders/waveaudioloader.h"
#include "fastFourierTransform/windowfunctions.h"
#include "audioTransforms/audiorecordtransforms.h"
#include "fastFourierTransform/wfft.h"
#include "tools.h"

#include <fstream>


using namespace std;

int main()
{
   /* AudioRecord ar =  WaveAudioLoader::loadAudioRecord("country.wav");


    int prefix_size,suffix_size;
    ar = AudioRecordTransforms::SizingToPowerOfTwo::perform(ar,prefix_size,suffix_size);

    cout << prefix_size << endl;
    cout << suffix_size << endl;

    HannWindowFunction hWindow;
    vector<complex> result;

    cout << WFFT::perform(ar.getData()[0],result,hWindow,1024) << endl;

    cout << ar.channelDataSize << endl;

    ofstream out_stream;
    out_stream.open("out.txt",ios_base::out);
    for(int i = 0; i < result.size(); i++)
        //out_stream << sqrt(pow(result[i].re(),2) + pow(result[i].im(),2)) << endl;
        //out_stream << atan(result[i].re()/result[i].im()) << endl;
        out_stream << result[i].re() << " " << result[i].im() << endl;*/
    return 0;
}

