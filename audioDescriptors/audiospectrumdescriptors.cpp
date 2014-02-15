#include "audiospectrumdescriptors.h"

// --- Base Class ---
AudioSpectrumDescriptorExtractor::AudioSpectrumDescriptorExtractor(AudioAmpSpectrum &spectrum, int result_count) : AudioDescriptorExtractor(){
    this->spectrum = spectrum;
    if(result_count > spectrum.getChannelDataSize())
        this->result_count = spectrum.getChannelDataSize();
    else
        this->result_count = result_count;
;
}

std::vector<double> AudioSpectrumDescriptorExtractor::getAverageValues(std::vector< std::vector<double> > &channels_values, int result_frames_count){
    std::vector<double> result_values;
    result_values.resize(result_frames_count);

    int channels_count = this->spectrum.getChannelsCount();
    int frames_count = this->spectrum.getChannelDataSize();

    int step = frames_count / result_frames_count;

    int frame, it;
    double frame_temp;

    // for 0 .. result_frames_count - 1
    for(frame = 0; frame < result_frames_count - 1; frame++){
        frame_temp = 0.0;
        it = frame * step;
        for(int i = it; i < it+step; i++)
            for(int ch = 0; ch < channels_count; ch++)
                frame_temp += channels_values[ch][i];

        result_values[frame] = frame_temp / (channels_count * step);
    }

    // last frame
    frame_temp = 0.0;
    it = frame * step;
    for(int i = it; i < frames_count; i++)
        for(int ch = 0; ch < channels_count; ch++)
            frame_temp += channels_values[ch][i];

    result_values[frame] = frame_temp / (channels_count * (frames_count - it));

    return result_values;
}

std::vector<double> AudioSpectrumDescriptorExtractor::extract(){
    std::vector < std::vector<double> > channels_values;

    int channels_count = this->spectrum.getChannelsCount();
    int frames_count = this->spectrum.getChannelDataSize();

    channels_values.resize(channels_count);

    for(int i = 0; i < channels_count; i++){
        channels_values[i].resize(frames_count);
        for(int j = 0; j < frames_count; j++)
            channels_values[i][j] = this->extractForOneFrame(i,j);
    }

    return this->getAverageValues(channels_values,this->result_count);
}
// --- ---------- ---




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
SpFluxDescriptorExtractor::SpFluxDescriptorExtractor(AudioAmpSpectrum &spectrum, int result_frames_count) : AudioSpectrumDescriptorExtractor(spectrum,result_frames_count){
}

double SpFluxDescriptorExtractor::extractForOneFrame(int channel_number, int frame_number){
    int fq_count = this->spectrum.getFrequencyCount();
    double temp = 0.0;
    double fq_temp;

    for(int fq_i = 0; fq_i < fq_count; fq_i++){
        switch (frame_number) {
        case 0:
            fq_temp = this->spectrum[channel_number][frame_number][fq_i];
            break;
        default:
            fq_temp = this->spectrum[channel_number][frame_number][fq_i] - this->spectrum[channel_number][frame_number - 1][fq_i];
            break;
        }
        temp += fq_temp * fq_temp;
    }

    return temp / fq_count ;
}

// --- ------------- ---
