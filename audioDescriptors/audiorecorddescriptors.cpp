#include "audioDescriptors/audiorecorddescriptors.h"

// --- Record Energy ---
EnergyDescriptorExtractor::EnergyDescriptorExtractor(AudioRecord &record) : AudioDescriptorExtractor(){
    this->record = record;
    this->fillResult();
}

<<<<<<< HEAD
bool EnergyDescriptorExtractor::fillResult(){
=======

std::vector<double> EnergyDescriptorExtractor::extract(){
>>>>>>> not-tested
    std::vector<double> temp_vector;
    int channels_count = record.getChannelsCount();
    int data_size = record.getChannelDataSize();
    temp_vector.resize(channels_count);

    double temp;

    for(int i = 0; i < channels_count; i++){
        temp = 0;
        for(int j = 0; j < data_size; j++){
            temp += pow(record[i][j],2);
        }
        temp_vector[i] = temp / data_size; // normalized
    }

    temp = Tools::getAverage(temp_vector);
    this->output_result.push_back(temp);

    return true;
}

// --- ------------- ---


// --- Record Zero Crossing Rate ---
ZCRDescriptorExtractor::ZCRDescriptorExtractor(AudioRecord &record) : AudioDescriptorExtractor(){
    this->record = record;
    this->fillResult();
}

bool ZCRDescriptorExtractor::fillResult(){
    std::vector<double> temp_vector;

    int channels_count = record.getChannelsCount();
    int data_size = record.getChannelDataSize();

    temp_vector.resize(channels_count);

    double temp;

    for(int i = 0; i < channels_count; i++){
        temp = 0;
        for(int j = 1; j < data_size; j++){
            temp += abs(Tools::signum(record[i][j]) - Tools::signum(record[i][j-1]));
        }
        temp_vector[i] = temp / (2 * data_size); // normalized
    }

    temp = Tools::getAverage(temp_vector);
    this->output_result.push_back(temp);

    return true;
}
<<<<<<< HEAD

// --- ------------------------- ---


=======
>>>>>>> not-tested
