#include <iostream>
#include "audioLoaders/waveaudioloader.h"
#include "audioSavers/audiosavers.h"
#include "audioTransforms/audiowfft.h"
#include "audioTransforms/audiorecordtransforms.h"
#include "audioTransforms/audiospectrumtransforms.h"
#include "audioDescriptors/audiodescriptorextractor.h"
#include "audioDescriptors/audiospectrumdescriptors.h"
#include "audioDescriptors/audiorecorddescriptors.h"


#include <ctime>
#include <fstream>


using namespace std;

int main(int argc, char *argv[])
{
    try{
        /*if(argc < 2) {
            cerr <<"Use: <programname> <filename>"<<endl;
            return 1;
        }*/

        AudioRecord ar =  WaveAudioLoader::loadAudioRecord(argv[1]);

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

        int result_size = 1;

        ZCRDescriptorExtractor zcr_de(ar);
        EnergyDescriptorExtractor energy_de(ar);
        SpFluxDescriptorExtractor spflux_de(amp_sp_clear,result_size);
        SpFlatnessDescriptorExtractor spflat_de(amp_sp_filtered,result_size);
        SpCentroidDescriptorExtractor spcen_de(amp_sp_clear,result_size);
        SpRollOffDescriptorExtractor sproll_de(amp_sp_clear,result_size);

        AudioDescriptorCollector dc;
        dc.addDescriptorExtractor(zcr_de);
        dc.addDescriptorExtractor(energy_de);
        dc.addDescriptorExtractor(spflux_de);
        dc.addDescriptorExtractor(spflat_de);
        dc.addDescriptorExtractor(spcen_de);
        dc.addDescriptorExtractor(sproll_de);

        std::vector<double> out = dc.extract();

        for(int i = 0; i < out.size(); i++)
            cout<<i+1<<":"<<out[i]<<" ";

       return 0;
    }
    catch(exception &ex){
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    // TODO : mfcc descriptor extractor
    // one of descriptors return nan number 5 may be spcen
}

