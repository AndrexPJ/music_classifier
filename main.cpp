#include "audioLoaders/waveaudioloader.h"
#include "audioSavers/audiosavers.h"
#include "audioTransforms/audiowfft.h"
#include "audioTransforms/audiodwt.h"
#include "audioTransforms/audiorecordtransforms.h"
#include "audioTransforms/audiospectrumtransforms.h"
#include "audioDescriptors/audiodescriptorextractor.h"
#include "audioDescriptors/audiospectrumdescriptors.h"
#include "audioDescriptors/audiorecorddescriptors.h"
#include "audioDescriptors/audiorhythmdescriptors.h"
#include "audioDescriptors/audiotonalitydescriptors.h"
#include "audioTransforms/audiowavelettransforms.h"

#include <iostream>
#include <fstream>


using namespace std;

int main(int argc, char *argv[])
{
    try{
        string filename;
        if(argc < 2)
            filename = "classical2.wav";
        else
            filename = argv[1];

        AudioRecord ar =  WaveAudioLoader::loadAudioRecord(filename);

        //AudioRecord ar_lp_filtered = AudioRecordTransforms::performLowPassFilter(ar,50.0);
        //AudioRecord ar_hp_filtered = AudioRecordTransforms::performHighPassFilter(ar,10000.0);
        //AudioRecord ar_filtered = AudioRecordTransforms::performPreEmphasisFilter(ar,0.95);

        //int window_size = 2048;
        //int hop_size = window_size * 0.5; // 2048 window_size and hop_size = 0.5 * window_size is a best for audio analysing

        int window_size_rhythm = 2048;
        int hop_size_rhythm = window_size_rhythm;
        HanningWindowFunction wf_rhythm(window_size_rhythm);

        //HanningWindowFunction wf(window_size);

        //AudioSpectrum<complex> sp_clear;
        //AudioSpectrum<complex> sp_filtered;
        //AudioSpectrum<complex> sp_pitch;
        AudioSpectrum<complex> sp_rhythm;
        AudioWFFT::perform(ar,sp_rhythm,wf_rhythm,hop_size_rhythm);
        AudioAmpSpectrum amp_sp_rhythm = AudioSpectrumTransforms::getAmpSpectrum(sp_rhythm);
        AudioBeatSpectrum beat_sp = AudioSpectrumTransforms::getBeatSpectrum(amp_sp_rhythm);



        ofstream out_stream;
        out_stream.open("out.txt",ios_base::out);

        double koeff = double(window_size_rhythm) / ar.getSampleRate();
        int N = beat_sp.getChannelDataSize();
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                out_stream << koeff * i << " " << koeff * j  << " " << beat_sp[0][i][j] << endl;

        out_stream.close();

        //AudioWFFT::perform(ar,sp_clear,wf,hop_size);
        //AudioWFFT::perform(ar_filtered,sp_filtered,wf,hop_size);
        //AudioWFFT::perform(ar_lp_filtered,sp_lp_rhythm,wf,hop_size_rhythm);
        //AudioWFFT::perform(ar,sp_pitch,wf,window_size);

        //AudioAmpSpectrum amp_sp_lp_rhythm = AudioSpectrumTransforms::getAmpSpectrum(sp_lp_rhythm);
        //AudioAmpSpectrum amp_sp_clear = AudioSpectrumTransforms::getAmpSpectrum(sp_clear);
        //AudioAmpSpectrum amp_sp_filtered = AudioSpectrumTransforms::getAmpSpectrum(sp_filtered);

        //AudioAmpSpectrum amp_sp_pitch = AudioSpectrumTransforms::getAmpSpectrum(sp_pitch);
        //AudioPitchChroma pch = AudioSpectrumTransforms::getPitchChroma(amp_sp_clear);

       // int result_size = 1;

        //ofstream out_stream;
        //out_stream.open("out.txt",ios_base::out);

        /*for(int i = 0; i < pch.getChannelDataSize(); i++){
            for(int j = 0; j < pch.getFrequencyCount(); j++){

                for(int k = 0; k < 20; k++)
                    out_stream << i << " " << 20*j + k << " "<< (pch[0][i][j]) << endl;
            }
        }*/

        /*for(int i = 0; i < amp_sp_clear.getChannelDataSize(); i++){
            for(int j = 0; j < amp_sp_clear.getFrequencyCount(); j++){
                    out_stream << i << " " << j << " "<< (amp_sp_clear[0][i][j]) << endl;
            }
        }*/

        //out_stream.close();

       //HainsworthNoveltyFunction flux_lp_nf(amp_sp_lp_rhythm);
       //AutocorrelationFunction cr_f(flux_lp_nf.getValues()[0]);

       //double koeff = 60 * (double(ar.getSampleRate()) / window_size);

       /*ofstream out_stream;
       out_stream.open("out.txt",ios_base::out);

       for(int i = 1; i < cr_f.getIntervalSize() / 2; i++){
           if(i > koeff/50) break;
           if(i < koeff/240) continue;
           out_stream << i << " " << cr_f.perform(i) << endl;
       }

       out_stream.close();*/



       // HainsworthNoveltyFunction flux_hp_nf(amp_sp_hp_rhythm);
       // AutocorrelationFunction cr_f(flux_lp_nf.getValues()[0]);

        //ZCRDescriptorExtractor zcr_de(ar);
        //EnergyDescriptorExtractor energy_de(ar);

        //SpFluxDescriptorExtractor spflux_de(amp_sp_clear,result_size);
        //SpFlatnessDescriptorExtractor spflat_de(amp_sp_filtered,result_size);
        //SpCentroidDescriptorExtractor spcen_de(amp_sp_clear,result_size);
        //SpRollOffDescriptorExtractor sproll_de(amp_sp_clear,result_size);

        //MFCCDescriptorExtractor mfcc_de(amp_sp_clear);

        //HistogramDescriptorExtractor h_de(pch);
        //SpFluxDescriptorExtractor spflux_pch_de(pch,result_size);
        //SpFlatnessDescriptorExtractor spflat_pch_de(pch,result_size);
        //SpCentroidDescriptorExtractor spcen_pch_de(pch,result_size);
        //SpRollOffDescriptorExtractor sproll_pch_de(pch,result_size);

        //BeatHistogramDescriptorExtractor bh_de(cr_f,koeff);

        //AudioDescriptorCollector dc;
        //dc.addDescriptorExtractor(h_de);
        //dc.addDescriptorExtractor(bh_de);
        //dc.addDescriptorExtractor(zcr_de);
        //dc.addDescriptorExtractor(energy_de);
        //dc.addDescriptorExtractor(spflux_de);
        //dc.addDescriptorExtractor(spflat_de);
        //dc.addDescriptorExtractor(spcen_de);
        //dc.addDescriptorExtractor(sproll_de);
        //dc.addDescriptorExtractor(mfcc_de);

        //dc.addDescriptorExtractor(spflux_pch_de);
        //dc.addDescriptorExtractor(spflat_pch_de);
        //dc.addDescriptorExtractor(spcen_pch_de);
        //dc.addDescriptorExtractor(sproll_pch_de);

        //std::vector<double> out = dc.extract();

        //double sum = 0.0;

        //for(int i = 0; i < out.size(); i++){
            //cout << i << " " << out[i] << endl;
            //cout << out[i]<<" ";
           //cout<<i+1<<":"<<out[i]<<" ";
        //}
       return 0;
    }
    catch(exception &ex){
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    // TODO : 2dmin autocorr (fft)
    // TODO : mfcc descriptor extractor
}

