#include "audiodescriptorfactory.h"

AudioDescriptorExtractorFactory::AudioDescriptorExtractorFactory(AudioRecord &ar){
    this->type_map["ZCR"] = new ZCRDescriptorFactory(ar);
    this->type_map["ENERGY"] = new EnergyDescriptorFactory(ar);
    this->type_map["BEATHISTO"] = new BeatHistogramDescriptorFactory(ar);
    this->type_map["OTHER"] =  new SpectralDescriptorFactory(ar);
}

AudioDescriptorExtractor* AudioDescriptorExtractorFactory::getAudioDescriptor(std::string type){
    if(type == "OTHER") return NULL;

    if(this->type_map[type])
        return this->type_map[type]->getAudioDescriptor(type);
    else
        return this->type_map["OTHER"]->getAudioDescriptor(type);
}


AudioDecriptorCollectorFactory::AudioDecriptorCollectorFactory(AudioRecord &ar){
    this->de_factory = new AudioDescriptorExtractorFactory(ar);
}

AudioDecriptorCollectorFactory::~AudioDecriptorCollectorFactory(){
    delete this->de_factory;
}

AudioDescriptorCollector* AudioDecriptorCollectorFactory::getAudioDescriptorCollector(std::vector<std::string> &types){
    AudioDescriptorCollector *ad_collector = new AudioDescriptorCollector();
    AudioDescriptorExtractor *temp_extractor;
    for(std::vector<std::string>::iterator it = types.begin(); it != types.end();it++){
        temp_extractor = this->de_factory->getAudioDescriptor(*it);
        if(temp_extractor)
            ad_collector->addDescriptorExtractor(*temp_extractor);
    }
    return ad_collector;
}

AudioDescriptorCollector* AudioDecriptorCollectorFactory::getAudioDescriptorCollector(std::string types[], int count){
    std::vector<std::string> v_types(types,types+count);
    return this->getAudioDescriptorCollector(v_types);
}

// --- ------------------------- ---

// --- record descriptors factories ---
EnergyDescriptorFactory::EnergyDescriptorFactory(AudioRecord &ar){
    this->ar = ar;
}

AudioDescriptorExtractor* EnergyDescriptorFactory::getAudioDescriptor(std::string type){
    return new EnergyDescriptorExtractor(this->ar);
}


ZCRDescriptorFactory::ZCRDescriptorFactory(AudioRecord &ar){
    this->ar = ar;
}

AudioDescriptorExtractor* ZCRDescriptorFactory::getAudioDescriptor(std::string type){
    return new ZCRDescriptorExtractor(this->ar);
}

// --- --------------------------- ---

// --- spectral descriptors factories ---
void SpectralDescriptorFactory::initTypeMap(){
    this->type_map["SPFLATNESS"] = new SpFlatnessDescriptorFactory(this->amp_spectrum);
    this->type_map["SPFLUX"] = new SpFluxDescriptorFactory(this->amp_spectrum);
    this->type_map["SPCENTROID"] = new SpCentroidDescriptorFactory(this->amp_spectrum);
    this->type_map["SPROLLOFF"] = new SpRollOffDescriptorFactory(this->amp_spectrum);
    this->type_map["PITCHHISTO"] = new PitchHistogramDescriptorFactory(this->amp_spectrum);
    this->type_map["MFCC"] = new MFCCDescriptorFactory(this->amp_spectrum);
}

SpectralDescriptorFactory::SpectralDescriptorFactory(){
}

SpectralDescriptorFactory::SpectralDescriptorFactory(AudioRecord &ar){
    int window_size = 2048;
    int hop_size = 1024;
    HanningWindowFunction wf(window_size);

    AudioSpectrum<complex> temp_spectrum;
    AudioWFFT::perform(ar,temp_spectrum,wf,hop_size);

    this->amp_spectrum = AudioSpectrumTransforms::getAmpSpectrum(temp_spectrum);
    this->initTypeMap();
}

SpectralDescriptorFactory::SpectralDescriptorFactory(AudioSpectrum<double> &amp_spectrum){
    this->amp_spectrum = amp_spectrum;
}


SpFluxDescriptorFactory::SpFluxDescriptorFactory(AudioSpectrum<double> &amp_spectrum) : SpectralDescriptorFactory(amp_spectrum){}

AudioDescriptorExtractor* SpFluxDescriptorFactory::getAudioDescriptor(std::string type){
    return new SpFluxDescriptorExtractor(this->amp_spectrum);
}

SpFlatnessDescriptorFactory::SpFlatnessDescriptorFactory(AudioSpectrum<double> &amp_spectrum) : SpectralDescriptorFactory(amp_spectrum){}

AudioDescriptorExtractor* SpFlatnessDescriptorFactory::getAudioDescriptor(std::string type){
    return new SpFlatnessDescriptorExtractor(this->amp_spectrum);
}

SpCentroidDescriptorFactory::SpCentroidDescriptorFactory(AudioSpectrum<double> &amp_spectrum) : SpectralDescriptorFactory(amp_spectrum){}

AudioDescriptorExtractor* SpCentroidDescriptorFactory::getAudioDescriptor(std::string type){
    return new SpCentroidDescriptorExtractor(this->amp_spectrum);
}

SpRollOffDescriptorFactory::SpRollOffDescriptorFactory(AudioSpectrum<double> &amp_spectrum) : SpectralDescriptorFactory(amp_spectrum){}

AudioDescriptorExtractor* SpRollOffDescriptorFactory::getAudioDescriptor(std::string type){
    return new SpRollOffDescriptorExtractor(this->amp_spectrum);
}

PitchHistogramDescriptorFactory::PitchHistogramDescriptorFactory(AudioSpectrum<double> &amp_spectrum) {
    this->amp_spectrum = AudioSpectrumTransforms::getPitchChroma(amp_spectrum);
}

AudioDescriptorExtractor* PitchHistogramDescriptorFactory::getAudioDescriptor(std::string type){
    return new HistogramDescriptorExtractor(this->amp_spectrum);
}


MFCCDescriptorFactory::MFCCDescriptorFactory(AudioSpectrum<double> &amp_spectrum) : SpectralDescriptorFactory(amp_spectrum){}

AudioDescriptorExtractor* MFCCDescriptorFactory::getAudioDescriptor(std::string type){
    return new MFCCDescriptorExtractor(this->amp_spectrum);
}

BeatHistogramDescriptorFactory::BeatHistogramDescriptorFactory(AudioRecord &ar){
    int window_size_rhythm = 1024;
    HanningWindowFunction wf_rhythm(window_size_rhythm);
    AudioSpectrum<complex> sp_lp_rhythm;

    AudioRecord ar_lp_filtered = AudioRecordTransforms::performLowPassFilter(ar,50.0);
    AudioWFFT::perform(ar_lp_filtered,sp_lp_rhythm,wf_rhythm,window_size_rhythm);
    AudioAmpSpectrum amp_sp_lp_rhythm = AudioSpectrumTransforms::getAmpSpectrum(sp_lp_rhythm);
    HainsworthNoveltyFunction novelty_function(amp_sp_lp_rhythm);

    this->correlation_f = AutocorrelationFunction(novelty_function.getValues()[0]);
    this->koeff = 60 * (double(ar.getSampleRate()) / window_size_rhythm);
}

AudioDescriptorExtractor* BeatHistogramDescriptorFactory::getAudioDescriptor(std::string type){
    return new BeatHistogramDescriptorExtractor(this->correlation_f,koeff);
}

// --- ------------------------------ ---
