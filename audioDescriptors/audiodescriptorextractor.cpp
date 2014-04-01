#include "audiodescriptorextractor.h"

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

bool AudioDescriptorCollector::addDescriptorExtractor(AudioDescriptorExtractor &de){
    this->de_vector.push_back(&de);
    return true;
}

std::vector<double> AudioDescriptorCollector::extract(){
 std::vector<double> result;
 std::vector<double> temp;
 for(std::vector<AudioDescriptorExtractor*>::iterator it = this->de_vector.begin(); it != this->de_vector.end(); it++){
     if(*it){
        temp = (*it)->extract();
        result.insert(result.end(),temp.begin(),temp.end());
     }
 }
 return result;
}


BaseDescriptorFactory::BaseDescriptorFactory(AudioRecord &ar){}
BaseDescriptorFactory::BaseDescriptorFactory(){}
BaseDescriptorFactory::~BaseDescriptorFactory(){
    for(std::map< std::string, BaseDescriptorFactory*>::iterator it = this->type_map.begin(); it!= this->type_map.end(); it++)
        delete (*it).second;
}

AudioDescriptorExtractor* BaseDescriptorFactory::getAudioDescriptor(std::string type){
        return this->type_map[type]->getAudioDescriptor(type);
}
