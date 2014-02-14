#include "audioDescriptors/audiorecorddescriptors.h"

EnergyDescriptorExtractor::EnergyDescriptorExtractor(AudioRecord &record) : AudioDescriptorExtractor(){
    this->record = record;
}

std::vector<double> EnergyDescriptorExtractor::extract(){
    std::vector<double> temp_vector;
    temp_vector.resize(record.channelsCount);

    double temp;

    for(int i = 0; i < record.channelsCount; i++){
        temp = 0;
        for(int j = 0; j < record.channelDataSize; j++){
            temp += pow(record[i][j],2);
        }
        temp_vector[i] = temp/record.channelDataSize; // normalized
    }

    temp = Tools::getAverage(temp_vector);

    temp_vector.clear();
    temp_vector.push_back(temp);
    return temp_vector;
}



ZCRDescriptorExtractor::ZCRDescriptorExtractor(AudioRecord &record) : AudioDescriptorExtractor(){
    this->record = record;
}

std::vector<double> ZCRDescriptorExtractor::extract(){
    std::vector<double> temp_vector;
    temp_vector.resize(record.channelsCount);

    double temp;

    for(int i = 0; i < record.channelsCount; i++){
        temp = 0;
        for(int j = 1; j < record.channelDataSize; j++){
            temp += abs(Tools::signum(record[i][j]) - Tools::signum(record[i][j-1]));
        }
        temp_vector[i] = temp/(2 * record.channelDataSize); // normalized
    }

    temp = Tools::getAverage(temp_vector);

    temp_vector.clear();
    temp_vector.push_back(temp);
    return temp_vector;

}



