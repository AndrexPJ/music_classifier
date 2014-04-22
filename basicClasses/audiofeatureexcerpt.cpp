#include "audiofeatureexcerpt.h"

AudioFeatureExcerpt::AudioFeatureExcerpt() : std::pair<std::vector<std::vector<double> >, std::vector<double> >(){}

AudioFeatureExcerpt::AudioFeatureExcerpt(std::vector<std::vector<double> > &feature_samples, std::vector<double> &labels)
                     : std::pair<std::vector<std::vector<double> >, std::vector<double> >(feature_samples,labels){}

AudioFeatureExcerpt::AudioFeatureExcerpt(std::vector<std::vector<double> > &feature_samples, std::vector<double> &labels, std::vector<std::string> &class_names)
                     : std::pair<std::vector<std::vector<double> >, std::vector<double> >(feature_samples,labels)
{
    this->class_names = class_names;
}

std::vector<std::vector<double> > AudioFeatureExcerpt::getFeatureSamples() const{
    return this->first;
}

std::vector<double> AudioFeatureExcerpt::getLabels() const{
    return this->second;
}

std::vector<std::string> AudioFeatureExcerpt::getClassNames() const{
    return this->class_names;
}

int AudioFeatureExcerpt::getSize() const{
    return this->first.size();
}
