#include "audiodescriptorextractor.h"

AudioDescriptorExtractor::AudioDescriptorExtractor(){}

<<<<<<< HEAD
bool AudioDescriptorExtractor::fillResult(){
return false;
}


AudioDescriptorExtractor::AudioDescriptorExtractor(const AudioDescriptorExtractor &extractor){
    this->output_result = extractor.extract();
}

std::vector<double> AudioDescriptorExtractor::extract() const{
    return this->output_result;
}
=======
AudioDescriptorExtractor::~AudioDescriptorExtractor(){}
>>>>>>> not-tested

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
    this->de_vector.push_back(de);
    return true;
}

std::vector<double> AudioDescriptorCollector::extract(){
 std::vector<double> result;
 std::vector<double> temp;
<<<<<<< HEAD



 for(std::vector<AudioDescriptorExtractor>::iterator it = this->de_vector.begin(); it != this->de_vector.end(); it++){
     temp = (*it).extract();
     result.insert(result.end(),temp.begin(),temp.end());
=======
 for(std::vector<AudioDescriptorExtractor*>::iterator it = this->de_vector.begin(); it != this->de_vector.end(); it++){
     if(*it){
        temp = (*it)->extract();
        result.insert(result.end(),temp.begin(),temp.end());
     }
>>>>>>> not-tested
 }
 return result;
}


<<<<<<< HEAD
 /* double norm = 0.0;
  for(std::vector<double>::iterator it = result.begin(); it != result.end(); it++){
     norm += (*it) * (*it) ;
 }
 norm = sqrt(norm);

 for(std::vector<double>::iterator it = result.begin(); it != result.end(); it++){
     (*it) /= norm;
     //(*it) = (*it) * 2 - 1;
 }*/
=======
BaseDescriptorFactory::BaseDescriptorFactory(AudioRecord &ar){}
BaseDescriptorFactory::BaseDescriptorFactory(){}
BaseDescriptorFactory::~BaseDescriptorFactory(){
    for(std::map< std::string, BaseDescriptorFactory*>::iterator it = this->type_map.begin(); it!= this->type_map.end(); it++)
        delete (*it).second;
}
>>>>>>> not-tested

AudioDescriptorExtractor* BaseDescriptorFactory::getAudioDescriptor(std::string type){
        return this->type_map[type]->getAudioDescriptor(type);
}
