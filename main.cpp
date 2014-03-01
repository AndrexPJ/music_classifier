#include <iostream>
#include "audioLoaders/waveaudioloader.h"
#include "audioSavers/audiosavers.h"
#include "audioTransforms/audiowfft.h"
#include "audioTransforms/audiorecordtransforms.h"
#include "audioTransforms/audiospectrumtransforms.h"
#include "audioDescriptors/audiodescriptorextractor.h"
#include "audioDescriptors/audiospectrumdescriptors.h"
#include "audioDescriptors/audiorecorddescriptors.h"
#include "audioDescriptors/audiorhythmdescriptors.h"

#include <ctime>
#include <fstream>


using namespace std;

int main(int argc, char *argv[])
{
    try{

        AudioRecord ar =  WaveAudioLoader::loadAudioRecord(argv[1]);
        ar = AudioRecordTransforms::performDCRemoval(ar);

        AudioRecord ar_lp_filtered = AudioRecordTransforms::performLowPassFilter(ar,50.0);
        AudioRecord ar_hp_filtered = AudioRecordTransforms::performHighPassFilter(ar,10000.0);
        AudioRecord ar_filtered = AudioRecordTransforms::performPreEmphasisFilter(ar,0.95);

        int window_size = 2048;
        int hop_size = window_size * 0.5; // 2048 window_size and hop_size = 0.5 * window_size is a best for audio analysing
        int hop_size_rhythm = window_size;
        HanningWindowFunction wf(window_size);

        AudioSpectrum<complex> sp_clear;
        AudioSpectrum<complex> sp_filtered;
        AudioSpectrum<complex> sp_lp_rhythm;
        AudioSpectrum<complex> sp_hp_rhythm;

        AudioWFFT::perform(ar,sp_clear,wf,hop_size);
        AudioWFFT::perform(ar_filtered,sp_filtered,wf,hop_size);
        AudioWFFT::perform(ar_lp_filtered,sp_lp_rhythm,wf,hop_size_rhythm);
        AudioWFFT::perform(ar_hp_filtered,sp_hp_rhythm,wf,hop_size_rhythm);

        AudioAmpSpectrum amp_sp_hp_rhythm = AudioSpectrumTransforms::getAmpSpectrum(sp_hp_rhythm);
        AudioAmpSpectrum amp_sp_lp_rhythm = AudioSpectrumTransforms::getAmpSpectrum(sp_lp_rhythm);
        AudioAmpSpectrum amp_sp_clear = AudioSpectrumTransforms::getAmpSpectrum(sp_clear);
        AudioAmpSpectrum amp_sp_filtered = AudioSpectrumTransforms::getAmpSpectrum(sp_filtered);

        int result_size = 1;

        HainsworthNoveltyFunction flux_lp_nf(amp_sp_lp_rhythm);
        //HainsworthNoveltyFunction flux_hp_nf(amp_sp_hp_rhythm);

        AutocorrelationFunction cr_f(flux_lp_nf.getValues()[0]);

        /*ofstream out_stream;
        out_stream.open("out.txt",ios_base::out);


        for(int i = 1; i < cr_f.getIntervalSize()/2; i++)
            out_stream << cr_f.perform(i) << endl;*/

        ZCRDescriptorExtractor zcr_de(ar);
        EnergyDescriptorExtractor energy_de(ar);
        SpFluxDescriptorExtractor spflux_de(amp_sp_clear,result_size);
        SpFlatnessDescriptorExtractor spflat_de(amp_sp_filtered,result_size);
        SpCentroidDescriptorExtractor spcen_de(amp_sp_clear,result_size);
        SpRollOffDescriptorExtractor sproll_de(amp_sp_clear,result_size);
        MFCCDescriptorExtractor mfcc_de(amp_sp_clear);


        BeatHistogramDescriptorExtractor bh_de(cr_f);
        AudioDescriptorCollector dc; 
        //dc.addDescriptorExtractor(bh_de);
        //dc.addDescriptorExtractor(zcr_de);
        //dc.addDescriptorExtractor(energy_de);
        //dc.addDescriptorExtractor(spflux_de);
        //dc.addDescriptorExtractor(spflat_de);
        //dc.addDescriptorExtractor(spcen_de);
        //dc.addDescriptorExtractor(sproll_de);
        dc.addDescriptorExtractor(mfcc_de);

        std::vector<double> out = dc.extract();

        for(int i = 0; i < out.size(); i++)
            cout << out[i]<<" ";
            //cout<<i+1<<":"<<out[i]<<" ";

       return 0;
    }
    catch(exception &ex){
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    // TODO : mfcc descriptor extractor
}

