#ifndef AUDIODESCRIPTORFACTORY_H
#define AUDIODESCRIPTORFACTORY_H

#include "featureExtractionLibraries/audioDescriptors/audiodescriptorextractor.h"
#include "featureExtractionLibraries/audioDescriptors/audiorecorddescriptors.h"
#include "featureExtractionLibraries/audioDescriptors/audiospectrumdescriptors.h"
#include "featureExtractionLibraries/audioDescriptors/audiorhythmdescriptors.h"
#include "featureExtractionLibraries/audioDescriptors/audiotonalitydescriptors.h"

#include "featureExtractionLibraries/audioTransforms/audiowfft.h"
#include "featureExtractionLibraries/audioTransforms/audiospectrumtransforms.h"
#include "featureExtractionLibraries/audioTransforms/audiorecordtransforms.h"
#include "featureExtractionLibraries/specialFunctions/noveltyfunctions.h"

#include "featureExtractionLibraries/audioDescriptors/audioextradescriptors.h"

class AudioDescriptorExtractorFactory : public BaseDescriptorFactory{
protected:
    AudioRecord *ar;
public:
    AudioDescriptorExtractorFactory(AudioRecord &ar);
    ~AudioDescriptorExtractorFactory();
    AudioDescriptorExtractor* getAudioDescriptor(std::string type);
};


class AudioDescriptorCollectorFactory{
protected:
    AudioDescriptorExtractorFactory *de_factory;
public:
    AudioDescriptorCollectorFactory(AudioRecord &ar);
    AudioDescriptorCollectorFactory();
    ~AudioDescriptorCollectorFactory();
    AudioDescriptorCollector* getAudioDescriptorCollector(std::vector<std::string> &types);
    AudioDescriptorCollector* getAudioDescriptorCollector(std::string types[], int count);
};

class EnergyDescriptorFactory : public BaseDescriptorFactory{
protected:
    AudioRecord *ar;
public:
    EnergyDescriptorFactory(AudioRecord *ar);
    AudioDescriptorExtractor* getAudioDescriptor(std::string type);
};


class ZCRDescriptorFactory : public BaseDescriptorFactory{
protected:
    AudioRecord *ar;
public:
    ZCRDescriptorFactory(AudioRecord *ar);
    AudioDescriptorExtractor* getAudioDescriptor(std::string type);
};




class SpectralDescriptorFactory : public BaseDescriptorFactory{
protected:
    AudioSpectrum<double> *amp_spectrum;
    void initTypeMap();
public:
    SpectralDescriptorFactory();
    SpectralDescriptorFactory(AudioRecord *ar);
    SpectralDescriptorFactory(AudioSpectrum<double> *amp_spectrum);
    virtual ~SpectralDescriptorFactory();
};

class SpFluxDescriptorFactory : public SpectralDescriptorFactory{
public:
    SpFluxDescriptorFactory(AudioSpectrum<double> *amp_spectrum);
    AudioDescriptorExtractor* getAudioDescriptor(std::string type);
};

class SpFlatnessDescriptorFactory : public SpectralDescriptorFactory{
public:
    SpFlatnessDescriptorFactory(AudioSpectrum<double> *amp_spectrum);
    AudioDescriptorExtractor* getAudioDescriptor(std::string type);
};

class SpCentroidDescriptorFactory : public SpectralDescriptorFactory{
public:
    SpCentroidDescriptorFactory(AudioSpectrum<double> *amp_spectrum);
    AudioDescriptorExtractor* getAudioDescriptor(std::string type);
};

class SpRollOffDescriptorFactory : public SpectralDescriptorFactory{
public:
    SpRollOffDescriptorFactory(AudioSpectrum<double> *amp_spectrum);
    AudioDescriptorExtractor* getAudioDescriptor(std::string type);
};

class PitchHistogramDescriptorFactory : public SpectralDescriptorFactory{
public:
    PitchHistogramDescriptorFactory(AudioSpectrum<double> *amp_spectrum);
    AudioDescriptorExtractor* getAudioDescriptor(std::string type);
};

class MFCCDescriptorFactory : public SpectralDescriptorFactory{
public:
    MFCCDescriptorFactory(AudioSpectrum<double> *amp_spectrum);
    AudioDescriptorExtractor* getAudioDescriptor(std::string type);
};

class BeatHistogramDescriptorFactory : public BaseDescriptorFactory{
protected:
    AudioRecord *ar;
public:
    BeatHistogramDescriptorFactory(AudioRecord *ar);
    ~BeatHistogramDescriptorFactory();
    AudioDescriptorExtractor* getAudioDescriptor(std::string type);
};

class ClassifierDescriptorFactory : public BaseDescriptorFactory{
protected:
    AudioRecord *ar;
    std::vector<BasicClassifier*> classifiers;
public:
    ClassifierDescriptorFactory(AudioRecord *ar);
    ~ClassifierDescriptorFactory();
    AudioDescriptorExtractor* getAudioDescriptor(std::string type);
};

#endif // AUDIODESCRIPTORFACTORY_H
