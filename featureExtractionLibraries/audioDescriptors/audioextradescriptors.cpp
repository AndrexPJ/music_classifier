#include "audioextradescriptors.h"


// --- Classifier Descriptor ---

ClassifierDescriptorExtractor::ClassifierDescriptorExtractor(AudioRecord &ar, std::vector<BasicClassifier *> &classifiers, std::vector<std::string> &feature_names){
    this->classifiers = classifiers;
    this->feature_names = feature_names;
    this->ar = ar;
}

ClassifierDescriptorExtractor::ClassifierDescriptorExtractor(){}

ClassifierDescriptorExtractor::~ClassifierDescriptorExtractor(){
   /* for(int i = 0; i < this->classifiers.size(); i++){
        delete this->classifiers[i];
    }*/
}



AudioDescriptorExtractor* ClassifierDescriptorExtractor::clone(){
    return new ClassifierDescriptorExtractor(*this);
}

std::vector<double> ClassifierDescriptorExtractor::extract(){
    std::vector<double> result;
    AudioDescriptorCollectorFactory dc_factory(this->ar);
    AudioDescriptorCollector *dc = dc_factory.getAudioDescriptorCollector(feature_names);
    this->features = dc->extract();

    for(std::vector<BasicClassifier*>::iterator it = this->classifiers.begin(); it != this->classifiers.end(); it++){
        if((*it))
            result.push_back((*it)->classify(this->features));
    }

    return result;
}

// -----------------------------

