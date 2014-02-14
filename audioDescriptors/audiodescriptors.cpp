#include "audiodescriptors.h"

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


SpCentroidDescriptorExtractor::SpCentroidDescriptorExtractor(AudioAmpSpectrum &spectrum) : AudioDescriptorExtractor(){
    this->spectrum = spectrum;
}


std::vector<double> SpCentroidDescriptorExtractor::extract(){

    std::vector<double> temp_vector;
    temp_vector.resize(spectrum.channelsCount);

    double fq_amp_sum;
    double amp_sum;

    double temp_sum;

    for(int i = 0; i < spectrum.channelsCount; i++){
        temp_sum = 0;
        for(int j = 0; j < spectrum.channelDataSize; j++)
        {
            fq_amp_sum = 0;
            amp_sum = 0;
            for(int k = 0; k < spectrum.windowSize/2; k++){
                fq_amp_sum += spectrum.getFrequency(k) * spectrum[i][j][k];
                amp_sum += spectrum.getFrequency(k);
            }
            temp_sum += fq_amp_sum/amp_sum;
        }
        temp_vector[i] = temp_sum/spectrum.channelDataSize;
    }

    temp_sum = Tools::getAverage(temp_vector);

    temp_vector.clear();
    temp_vector.push_back(temp_sum);
    return temp_vector;

}


SpFlatnessDescriptorExtractor::SpFlatnessDescriptorExtractor(AudioAmpSpectrum &spectrum) : AudioDescriptorExtractor(){
    this->spectrum = spectrum;
}

std::vector<double> SpFlatnessDescriptorExtractor::extract(){
    std::vector < std::vector<double> > temp_vector;
    std::vector<double> out_vector;
    std::vector <int> bark_size;

    double gmean,amean,temp;
    double frequency, bark;
    double eps = std::numeric_limits<double>::epsilon();
    int bark_count = 24;

    out_vector.resize(bark_count);
    bark_size.resize(bark_count);
    temp_vector.resize(bark_count); // count of critical bands

    // vectors prepare
    for(int i = 0; i < bark_count; i++){
        bark_size[i] = 0;
        temp_vector[i].resize(spectrum.channelDataSize);
        for(int j = 0; j < spectrum.channelDataSize; j++)
            temp_vector[i][j] = 0.0;
    }

    // spectral power calculating
    for(int ch = 0; ch < spectrum.channelsCount; ch++){
        for(int fq_i = 0; fq_i < spectrum.windowSize/2; fq_i++){
            frequency = spectrum.getFrequency(fq_i);
            if(frequency < 105) continue;
            if(frequency > 22000) break;

            bark = AudioSpectrumTransforms::getCriticalBandRate(frequency) - 1;

            bark_size[bark]++;

            for(int i = 0; i < spectrum.channelDataSize; i++){
                temp_vector[bark][i] += spectrum[ch][i][fq_i] * spectrum[ch][i][fq_i];
            }

        }
    }


    //calculates gmean and amean
    for(int i = 0; i < bark_count; i++){
        out_vector[i] = 0.0;
        gmean = 0.0;
        amean = 0.0;

        for(int j = 0; j < spectrum.channelDataSize; j++){
           if(bark_size[i] != 0){
                temp = temp_vector[i][j]/bark_size[i];
                amean += temp;
                gmean += log(temp);
           }
        }

        if(amean <= eps)
            out_vector[i] = 0.0;
        else{
            gmean = exp(gmean/spectrum.channelDataSize);
            amean = amean/spectrum.channelDataSize;
            out_vector[i] = gmean / amean;
        }

    }

    temp_vector.clear();
    bark_size.clear();
    return out_vector;
}

