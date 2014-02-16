#include <iostream>
#include "audioLoaders/waveaudioloader.h"
#include "audioSavers/audiosavers.h"
#include "audioTransforms/audiowfft.h"
#include "audioTransforms/audiorecordtransforms.h"
#include "audioTransforms/audiospectrumtransforms.h"
#include "audioDescriptors/audiodescriptorextractor.h"
#include "audioDescriptors/audiospectrumdescriptors.h"

#include <fstream>


using namespace std;

int main(int argc, char *argv[])
{
    try{
        AudioRecord ar =  WaveAudioLoader::loadAudioRecord("neoclassical.wav");

        AudioRecord ar_filtered = AudioRecordTransforms::performPreEmphasisFilter(ar,0.95);

        int window_size = 2048;
        int hop_size = window_size * 0.5; // 2048 window_size and hop_size = 0.5 * window_size is a best for audio analysing
        HanningWindowFunction wf(window_size);

        AudioSpectrum<complex> sp;
        sp.setWindowSize(window_size);
        AudioWFFT::perform(ar_filtered,sp,wf,window_size,hop_size);
        AudioAmpSpectrum amp_sp = AudioSpectrumTransforms::getAmpSpectrum(sp);

        int result_size = 8;



        SpFluxDescriptorExtractor spflux_de(amp_sp);
        SpFlatnessDescriptorExtractor spflat_de(amp_sp);
        SpCentroidDescriptorExtractor spcen_de(amp_sp);

        vector<double> flux_out = spflux_de.extract();
        vector<double> flat_out = spflat_de.extract();
        vector<double> cen_out = spcen_de.extract();

        for(int i = 0; i < result_size; i++){
           cout << flux_out[i] << " " << flat_out[i] << " " << cen_out[i] << endl;
        }

        /*ofstream out_stream;
        out_stream.open("out.txt",ios_base::out);

        for(int i = 0; i < amp_sp.getChannelDataSize(); i++)
            for(int j = 0; j < amp_sp.getFrequencyCount(); j++){
                out_stream << amp_sp.getFrequency(j) << " " << amp_sp[0][i][j] << endl;
            }*/

        return 0;
    }
    catch(exception &ex){
        std::cerr << ex.what() << std::endl;
        return 1;
    }

}

