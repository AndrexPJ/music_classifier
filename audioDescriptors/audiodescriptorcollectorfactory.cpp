#include "audiodescriptorcollectorfactory.h"

AudioDescriptorCollector AudioDescriptorCollectorFactory::getDescriptorCollector(AudioRecord &ar, std::string extractors_names[],int names_count, int de_result_size){
    std::vector<std::string> names(extractors_names,extractors_names + names_count);
    return getDescriptorCollector(ar,names,de_result_size);
}

AudioDescriptorCollector AudioDescriptorCollectorFactory::getDescriptorCollector(AudioRecord &ar, std::vector<std::string> &extractors_names, int de_result_size){
    AudioDescriptorCollector dc;
    AudioDescriptorExtractor de;
    
    
    int window_size = 2048;
    int hop_size = window_size * 0.5;
    HanningWindowFunction wf(window_size);
    AudioSpectrum<complex> spectrum;
    AudioAmpSpectrum amp_spectrum;

    int window_size_rhythm = 1024;
    HanningWindowFunction wf_rhythm(window_size_rhythm);
    AudioSpectrum<complex> sp_lp_rhythm;
    AudioAmpSpectrum amp_sp_lp_rhythm;
    HainsworthNoveltyFunction novelty_function;
    AutocorrelationFunction correlation_f;

    AudioPitchChroma pitch_chroma;

    std::string name;
    for(int i = 0; i < extractors_names.size(); i++){
        name = extractors_names[i];

        if(name == ZCR_NAME){
            de = ZCRDescriptorExtractor(ar);
        }
        if(name == ENERGY_NAME){
            de = EnergyDescriptorExtractor(ar);
        }

        if((name == SPFLUX_NAME) || (name == SPFLATNESS_NAME) || (name == SPCENTROID_NAME) || (name == SPROLLOFF_NAME)
                                 || (name == PITCHHISTO_NAME) || (name == MFCC_NAME))
          {

            if(amp_spectrum.empty()){
                if(spectrum.empty())
                    AudioWFFT::perform(ar,spectrum,wf,hop_size);
                amp_spectrum = AudioSpectrumTransforms::getAmpSpectrum(spectrum);
            }


            if(name == SPFLUX_NAME)
                de = SpFluxDescriptorExtractor(amp_spectrum,de_result_size);
            if(name == SPFLATNESS_NAME)
                de = SpFlatnessDescriptorExtractor(amp_spectrum,de_result_size);
            if(name == SPCENTROID_NAME)
                de = SpCentroidDescriptorExtractor(amp_spectrum,de_result_size);
            if(name == SPROLLOFF_NAME)
                de = SpRollOffDescriptorExtractor(amp_spectrum,de_result_size);

            if(name == PITCHHISTO_NAME){
                if(pitch_chroma.empty())
                    pitch_chroma = AudioSpectrumTransforms::getPitchChroma(amp_spectrum);
                de = HistogramDescriptorExtractor(pitch_chroma);
            }

            if(name == MFCC_NAME)
                de = MFCCDescriptorExtractor(amp_spectrum);

        }

        if(name == BEATHISTO_NAME){
            AudioRecord ar_lp_filtered = AudioRecordTransforms::performLowPassFilter(ar,50.0);

            AudioWFFT::perform(ar_lp_filtered,sp_lp_rhythm,wf_rhythm,window_size_rhythm);
            amp_sp_lp_rhythm = AudioSpectrumTransforms::getAmpSpectrum(sp_lp_rhythm);

            novelty_function = HainsworthNoveltyFunction(amp_sp_lp_rhythm);
            correlation_f = AutocorrelationFunction(novelty_function.getValues()[0]);

            double koeff = 60 * (double(ar.getSampleRate()) / window_size_rhythm);
            de = BeatHistogramDescriptorExtractor(correlation_f,koeff);
        }


        dc.addDescriptorExtractor(de);
    }

    return dc;
}
