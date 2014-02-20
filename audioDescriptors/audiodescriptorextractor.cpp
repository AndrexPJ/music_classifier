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

 for(int i = 0; i < this->de_vector.size(); i++){
     temp = this->de_vector[i]->extract();
     result.insert(result.end(),temp.begin(),temp.end());
 }

 double norm = 0.0;
 //scaling
/* for(int i = 0; i < this->de_vector.size(); i++){
     norm += pow(result[i],2);
 }
 norm = sqrt(norm);

 for(int i = 0; i < this->de_vector.size(); i++){
     result[i] /= norm;
 }*/

 return result;

}
