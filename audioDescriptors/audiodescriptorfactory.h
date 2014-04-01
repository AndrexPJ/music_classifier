#ifndef AUDIODESCRIPTORFACTORY_H
#define AUDIODESCRIPTORFACTORY_H

#include "audioDescriptors/audiodescriptorextractor.h"
#include "audioDescriptors/audiorecorddescriptors.h"
#include "audioDescriptors/audiospectrumdescriptors.h"
#include "audioDescriptors/audiorhythmdescriptors.h"
#include "audioDescriptors/audiotonalitydescriptors.h"

#include "audioTransforms/audiowfft.h"
#include "audioTransforms/audiospectrumtransforms.h"
#include "audioTransforms/audiorecordtransforms.h"
#include "specialFunctions/noveltyfunctions.h"




class AudioDescriptorExtractorFactory : public BaseDescriptorFactory{
public:
    AudioDescriptorExtractorFactory(AudioRecord &ar);
    AudioDescriptorExtractor* getAudioDescriptor(std::string type);
};


class AudioDecriptorCollectorFactory{
protected:
    AudioDescriptorExtractorFactory *de_factory;
public:
    AudioDecriptorCollectorFactory(AudioRecord &ar);
    ~AudioDecriptorCollectorFactory();
    AudioDescriptorCollector* getAudioDescriptorCollector(std::vector<std::string> &types);
    AudioDescriptorCollector* getAudioDescriptorCollector(std::string types[], int count);
};

class EnergyDescriptorFactory : public BaseDescriptorFactory{
protected:
    AudioRecord ar;
public:
    EnergyDescriptorFactory(AudioRecord &ar);
    AudioDescriptorExtractor* getAudioDescriptor(std::string type);
};


class ZCRDescriptorFactory : public BaseDescriptorFactory{
protected:
    AudioRecord ar;
public:
    ZCRDescriptorFactory(AudioRecord &ar);
    AudioDescriptorExtractor* getAudioDescriptor(std::string type);
};




class SpectralDescriptorFactory : public BaseDescriptorFactory{
protected:
    AudioSpectrum<double> amp_spectrum;
    void initTypeMap();
public:
    SpectralDescriptorFactory();
    SpectralDescriptorFactory(AudioRecord &ar);
    SpectralDescriptorFactory(AudioSpectrum<double> &amp_spectrum);
};

class SpFluxDescriptorFactory : public SpectralDescriptorFactory{
public:
    SpFluxDescriptorFactory(AudioSpectrum<double> &amp_spectrum);
    AudioDescriptorExtractor* getAudioDescriptor(std::string type);
};

class SpFlatnessDescriptorFactory : public SpectralDescriptorFactory{
public:
    SpFlatnessDescriptorFactory(AudioSpectrum<double> &amp_spectrum);
    AudioDescriptorExtractor* getAudioDescriptor(std::string type);
};

class SpCentroidDescriptorFactory : public SpectralDescriptorFactory{
public:
    SpCentroidDescriptorFactory(AudioSpectrum<double> &amp_spectrum);
    AudioDescriptorExtractor* getAudioDescriptor(std::string type);
};

class SpRollOffDescriptorFactory : public SpectralDescriptorFactory{
public:
    SpRollOffDescriptorFactory(AudioSpectrum<double> &amp_spectrum);
    AudioDescriptorExtractor* getAudioDescriptor(std::string type);
};

class PitchHistogramDescriptorFactory : public SpectralDescriptorFactory{
public:
    PitchHistogramDescriptorFactory(AudioSpectrum<double> &amp_spectrum);
    AudioDescriptorExtractor* getAudioDescriptor(std::string type);
};

class MFCCDescriptorFactory : public SpectralDescriptorFactory{
public:
    MFCCDescriptorFactory(AudioSpectrum<double> &amp_spectrum);
    AudioDescriptorExtractor* getAudioDescriptor(std::string type);
};

class BeatHistogramDescriptorFactory : public BaseDescriptorFactory{
protected:
    CorrelationFunction correlation_f;
    double koeff;
public:
    BeatHistogramDescriptorFactory(AudioRecord &ar);
    AudioDescriptorExtractor* getAudioDescriptor(std::string type);
};

#endif // AUDIODESCRIPTORFACTORY_H
