#ifndef AUDIOEXTRADESCRIPTORS_H
#define AUDIOEXTRADESCRIPTORS_H

#include "classificationLibraries/boostclassifier.h"
#include "featureExtractionLibraries/audioDescriptors/audiodescriptorextractor.h"
#include "featureExtractionLibraries/audioDescriptors/audiodescriptorfactory.h"


class ClassifierDescriptorExtractor: public AudioDescriptorExtractor{
protected:
    std::vector<BasicClassifier *> classifiers;
    std::vector<double> features;
    std::vector<std::string> feature_names;
    AudioRecord ar;
public:
    ClassifierDescriptorExtractor(AudioRecord &ar, std::vector<BasicClassifier *> &classifiers,std::vector<std::string> &feature_names);
    ClassifierDescriptorExtractor();
    virtual ~ClassifierDescriptorExtractor();
    virtual std::vector<double> extract();
    AudioDescriptorExtractor* clone();
};

#endif // AUDIOEXTRADESCRIPTORS_H
