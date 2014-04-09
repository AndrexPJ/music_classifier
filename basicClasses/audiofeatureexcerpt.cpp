#include "audiofeatureexcerpt.h"

AudioFeatureExcerpt::AudioFeatureExcerpt() : std::pair<std::vector<std::vector<double> >, std::vector<double> >(){}

AudioFeatureExcerpt::AudioFeatureExcerpt(std::vector<std::vector<double> > &feature_samples, std::vector<double> &labels)
                     : std::pair<std::vector<std::vector<double> >, std::vector<double> >(feature_samples,labels){}

std::vector<std::vector<double> > AudioFeatureExcerpt::getFeatureSamples() const{
    return this->first;
}

std::vector<double> AudioFeatureExcerpt::getLabels() const{
    return this->second;
}


int AudioFeatureExcerpt::getSize() const{
    return this->first.size();
}
