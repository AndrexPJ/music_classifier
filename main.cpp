#include <iostream>
#include "audioLoaders/waveaudioloader.h"
#include "fastFourierTransform/windowfunctions.h"
#include "audiorecordtransforms.h"
#include "fastFourierTransform/wfft.h"
#include "tools.h"

#include <fstream>


using namespace std;

int main()
{
    AudioRecord ar =  WaveAudioLoader::loadAudioRecord("country.wav");

    ar = AudioRecordTransforms::sizingToPowerOfTwo::perform(ar);

    HannWindowFunction *hWindow = new HannWindowFunction();

    vector<complex> result;

    cout << WFFT::perform(ar.channelsData[0],result,hWindow,512,0) << endl;


    ofstream out_stream;
    out_stream.open("out.txt",ios_base::out);
    for(int i = 0; i < result.size(); i++)
        out_stream << sqrt(pow(result[i].re(),2) + pow(result[i].im(),2)) << endl;


    return 0;
}

