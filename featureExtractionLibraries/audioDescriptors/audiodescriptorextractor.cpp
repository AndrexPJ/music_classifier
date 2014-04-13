#include "audiodescriptorextractor.h"

/*Sample::Sample(){}
Sample::Sample(std::vector<double> &features, double label){
    this->features = features;
    this->label = label;
}*/


AudioDescriptorExtractor::AudioDescriptorExtractor(){}

AudioDescriptorExtractor::~AudioDescriptorExtractor(){}

std::vector<double> AudioDescriptorExtractor::extract(){
    return std::vector<double>();
}

AudioDescriptorCollector::AudioDescriptorCollector() : AudioDescriptorExtractor(){}

AudioDescriptorCollector::~AudioDescriptorCollector(){
    for(std::vector<AudioDescriptorExtractor*>::iterator it = this->de_vector.begin(); it != this->de_vector.end(); it++){
        delete (*it);
    }
}

bool AudioDescriptorCollector::addDescriptorExtractor(AudioDescriptorExtractor *de){
    AudioDescriptorExtractor *temp_de = de->clone();
    this->de_vector.push_back(temp_de);
    return true;
}

void AudioDescriptorCollector::normalize(std::vector<double> &vector){
    std::pair<std::vector<double>::iterator,std::vector<double>::iterator> minmax = std::minmax_element(vector.begin(),vector.end());

    for(std::vector<double>::iterator it = vector.begin(); it != vector.end(); it++)
        (*it)  = ((*it) - (*minmax.first)) / (*minmax.second) - 1.0;
}

std::vector<double> AudioDescriptorCollector::extract(){
 std::vector<double> result;
 std::vector<double> temp;
 for(std::vector<AudioDescriptorExtractor*>::iterator it = this->de_vector.begin(); it != this->de_vector.end(); it++){
     if(*it){
        temp = (*it)->extract();
        //this->normalize(temp);
        result.insert(result.end(),temp.begin(),temp.end());
     }
 }
 /*double mean = Tools::getGeneralizedMean(result,1);
 double variance = Tools::getVariance(result,mean);
 double standart_dv = sqrt(variance);

 for(std::vector<double>::iterator it = result.begin(); it != result.end(); it++)
     (*it) = ((*it) - mean) / standart_dv;

 //std::sort(result.begin(),result.end());*/

 return result;
}

AudioDescriptorExtractor* AudioDescriptorCollector::clone() const{
    return new AudioDescriptorCollector(*this);
}


BaseDescriptorFactory::BaseDescriptorFactory(AudioRecord *ar){}
BaseDescriptorFactory::BaseDescriptorFactory(){}
BaseDescriptorFactory::~BaseDescriptorFactory(){
    for(std::map< std::string, BaseDescriptorFactory*>::iterator it = this->type_map.begin(); it!= this->type_map.end(); it++)
        delete (*it).second;
}

AudioDescriptorExtractor* BaseDescriptorFactory::getAudioDescriptor(std::string type){
    if(this->type_map[type])
        return this->type_map[type]->getAudioDescriptor(type);
    else return NULL;
}


