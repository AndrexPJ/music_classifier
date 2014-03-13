#include "audiodescriptorextractor.h"

AudioDescriptorExtractor::AudioDescriptorExtractor(){}


AudioDescriptorCollector::AudioDescriptorCollector() : AudioDescriptorExtractor(){
    this->de_vector.resize(0);
}

bool AudioDescriptorCollector::addDescriptorExtractor(AudioDescriptorExtractor &de){
    this->de_vector.push_back(&de);
    return true;
}

std::vector<double> AudioDescriptorCollector::extract(){
 std::vector<double> result;
 std::vector<double> temp;



 for(std::vector<AudioDescriptorExtractor*>::iterator it = this->de_vector.begin(); it != this->de_vector.end(); it++){
     temp = (*it)->extract();
     result.insert(result.end(),temp.begin(),temp.end());
 }


 /* double norm = 0.0;
  for(std::vector<double>::iterator it = result.begin(); it != result.end(); it++){
     norm += (*it) * (*it);
 }
 norm = sqrt(norm);

 for(std::vector<double>::iterator it = result.begin(); it != result.end(); it++){
     (*it) /= norm;
     //(*it) = (*it) * 2 - 1;
 }*/

 return result;
}
