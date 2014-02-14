#include "audiospectrumdescriptors.h"


// --- Spectral Centroid ---
SpCentroidDescriptorExtractor::SpCentroidDescriptorExtractor(AudioAmpSpectrum &spectrum) : AudioDescriptorExtractor(){
    this->spectrum = spectrum;
}

std::vector<double> SpCentroidDescriptorExtractor::extract(){

    std::vector<double> temp_vector;
    int channels_count = spectrum.getChannelsCount();
    int data_size = spectrum.getChannelDataSize();
    int fq_count = spectrum.getFrequencyCount();

    temp_vector.resize(channels_count);

    double fq_amp_sum;
    double amp_sum;

    double temp_sum;

    for(int i = 0; i < channels_count; i++){
        temp_sum = 0;
        for(int j = 0; j < data_size; j++)
        {
            fq_amp_sum = 0;
            amp_sum = 0;
            for(int k = 0; k < fq_count; k++){
                fq_amp_sum += spectrum.getFrequency(k) * spectrum[i][j][k];
                amp_sum += spectrum.getFrequency(k);
            }
            temp_sum += fq_amp_sum/amp_sum;
        }
        temp_vector[i] = temp_sum/data_size;
    }

    temp_sum = Tools::getAverage(temp_vector);

    temp_vector.clear();
    temp_vector.push_back(temp_sum);
    return temp_vector;

}
// --- ----------------- ---


// --- Spectral Flatness ---
SpFlatnessDescriptorExtractor::SpFlatnessDescriptorExtractor(AudioAmpSpectrum &spectrum) : AudioDescriptorExtractor(){
    this->spectrum = spectrum;
}

std::vector<double> SpFlatnessDescriptorExtractor::extract(){
    std::vector < std::vector<double> > temp_vector;
    std::vector<double> out_vector;
    std::vector <int> bark_size;

    int channels_count = spectrum.getChannelsCount();
    int data_size = spectrum.getChannelDataSize();
    int fq_count = spectrum.getFrequencyCount();

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
        temp_vector[i].resize(data_size);
        for(int j = 0; j < data_size; j++)
            temp_vector[i][j] = 0.0;
    }

    // spectral power calculating
    for(int ch = 0; ch < channels_count; ch++){
        for(int fq_i = 0; fq_i < fq_count; fq_i++){
            frequency = spectrum.getFrequency(fq_i);
            if(frequency < 105) continue;
            if(frequency > 22000) break;

            bark = AudioSpectrumTransforms::getCriticalBandRate(frequency) - 1;

            bark_size[bark]++;

            for(int i = 0; i < data_size; i++){
                temp_vector[bark][i] += spectrum[ch][i][fq_i] * spectrum[ch][i][fq_i];
            }

        }
    }


    //calculates gmean and amean
    for(int i = 0; i < bark_count; i++){
        out_vector[i] = 0.0;
        gmean = 0.0;
        amean = 0.0;

        for(int j = 0; j < data_size; j++){
           if(bark_size[i] != 0){
                temp = temp_vector[i][j]/bark_size[i];
                amean += temp;
                gmean += log(temp);
           }
        }

        if(amean <= eps)
            out_vector[i] = 0.0;
        else{
            gmean = exp(gmean/data_size);
            amean = amean/data_size;
            out_vector[i] = gmean / amean;
        }

    }

    temp_vector.clear();
    bark_size.clear();
    return out_vector;
}
// --- ----------------- ---


// --- Spectral Flux ---
SpFluxDescriptorExtractor::SpFluxDescriptorExtractor(AudioAmpSpectrum &spectrum, int frames_count) : AudioDescriptorExtractor(){
    this->spectrum = spectrum;
    if(frames_count > spectrum.getChannelDataSize())
        this->frames_count = spectrum.getChannelDataSize();
    else
        this->frames_count = frames_count;
}

std::vector<double> SpFluxDescriptorExtractor::extract(){

    int data_size = this->spectrum.getChannelDataSize();
    int channels_count = this->spectrum.getChannelsCount();
    int fq_count = this->spectrum.getFrequencyCount();

    int step = data_size / this->frames_count;

    std::vector<double> out_vector;
    out_vector.resize(this->frames_count);

    double frame_temp, temp;
    int it, frame;

    for(frame = 0; frame < this->frames_count - 1; frame++){
        frame_temp = 0.0;
        it = frame * step;
        for(int i = it; i < it+step - 1; i++){
            for(int fq_i = 0; fq_i < fq_count; fq_i++){
                temp = 0.0;
                for(int ch = 0; ch < channels_count; ch++)
                    temp += spectrum[ch][i + 1][fq_i] - spectrum[ch][i][fq_i];

                temp = temp/channels_count;
                frame_temp += temp * temp;
                }
            frame_temp /= fq_count;
        }
        out_vector[frame] = frame_temp;
    }

    // --- last frame ---
    frame_temp = 0.0;
    it = frame * step;
    for(int i = it; i < data_size - 1; i++){
        for(int fq_i = 0; fq_i < fq_count; fq_i++){
            temp = 0.0;
            for(int ch = 0; ch < channels_count; ch++)
                temp += spectrum[ch][i + 1][fq_i] - spectrum[ch][i][fq_i];

            temp = temp/channels_count;
            frame_temp += temp * temp;
            }
        frame_temp /= fq_count;
        }
    out_vector[frame] = frame_temp;
    // --- --------- ---

    return out_vector;
}

// --- ------------- ---
