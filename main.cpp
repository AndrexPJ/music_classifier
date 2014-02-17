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
        AudioRecord ar =  WaveAudioLoader::loadAudioRecord("metal.wav");

        AudioRecord ar_filtered = AudioRecordTransforms::performPreEmphasisFilter(ar,0.95);

        //WaveAudioSaver::saveAudioRecord(ar_filtered,"neoclassical_f.wav");

        int window_size = 2048;
        int hop_size = window_size * 0.5; // 2048 window_size and hop_size = 0.5 * window_size is a best for audio analysing
        HanningWindowFunction wf(window_size);

        AudioSpectrum<complex> sp_clear;
        AudioSpectrum<complex> sp_filtered;

        AudioWFFT::perform(ar,sp_clear,wf,hop_size);
        AudioWFFT::perform(ar_filtered,sp_filtered,wf,hop_size);

        AudioAmpSpectrum amp_sp_clear = AudioSpectrumTransforms::getAmpSpectrum(sp_clear);
        AudioAmpSpectrum amp_sp_filtered = AudioSpectrumTransforms::getAmpSpectrum(sp_filtered);

        int result_size = 8;


        SpFluxDescriptorExtractor spflux_de(amp_sp_clear,result_size);
        SpFlatnessDescriptorExtractor spflat_de(amp_sp_filtered,result_size);
        SpCentroidDescriptorExtractor spcen_de(amp_sp_clear,result_size);
        SpRollOffDescriptorExtractor sproll_de(amp_sp_clear,result_size);

        vector<double> flux_out = spflux_de.extract();
        vector<double> flat_out = spflat_de.extract();
        vector<double> cen_out = spcen_de.extract();
        vector<double> roll_out = sproll_de.extract();

       for(int i = 0; i < result_size; i++){
           cout << flux_out[i] << " " << flat_out[i] << " " << cen_out[i] << " " << roll_out[i] << endl;
       }

       return 0;
    }
    catch(exception &ex){
        std::cerr << ex.what() << std::endl;
        return 1;
    }

}

