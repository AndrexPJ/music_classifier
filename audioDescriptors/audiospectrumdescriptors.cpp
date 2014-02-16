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
SpCentroidDescriptorExtractor::SpCentroidDescriptorExtractor(AudioAmpSpectrum &spectrum, int result_frames_count) : AudioSpectrumDescriptorExtractor(spectrum, result_frames_count){
}


double SpCentroidDescriptorExtractor::extractForOneFrame(int channel_number, int frame_number){
     int fq_count = spectrum.getFrequencyCount();
     double fq_amp_sum = 0.0;
     double amp_sum = 0.0;

     for(int fq_i = 0; fq_i < fq_count; fq_i++){
         fq_amp_sum += this->spectrum.getFrequency(fq_i) * this->spectrum[channel_number][frame_number][fq_i];
         amp_sum += this->spectrum[channel_number][frame_number][fq_i];
     }

     return (fq_amp_sum / (amp_sum * this->spectrum.getFrequency(1) * fq_count));
}
// --- ----------------- ---


// --- Spectral Flatness ---
SpFlatnessDescriptorExtractor::SpFlatnessDescriptorExtractor(AudioAmpSpectrum &spectrum, int result_frames_count) : AudioSpectrumDescriptorExtractor(spectrum,result_frames_count){
}

double SpFlatnessDescriptorExtractor::extractForOneFrame(int channel_number, int frame_number){
    int bark;
    int bark_count = 24;
    int fq_count = spectrum.getFrequencyCount();

    double gmean, amean, frequency, temp;
    double eps = std::numeric_limits<double>::epsilon();

    std::vector < double > temp_vector;
    temp_vector.resize(bark_count);

    std::vector <int> bark_size;
    bark_size.resize(bark_count);

    for(int i = 0; i < bark_count; i++){
        bark_size[i] = 0;
        temp_vector[i] = 0.0;
    }


    for(int fq_i = 0; fq_i < fq_count; fq_i++){
        frequency = this->spectrum.getFrequency(fq_i);
        if(frequency < 105) continue;
        if(frequency > 22000) break;

        bark = AudioSpectrumTransforms::getCriticalBandRate(frequency) - 1;
        bark_size[bark]++;
        temp_vector[bark] += this->spectrum[channel_number][frame_number][fq_i] * this->spectrum[channel_number][frame_number][fq_i];
    }

    amean = 0.0;
    gmean = 0.0;
    int bark_true_count = 0;

    for(int i = 0; i < bark_count; i++){
        if(bark_size[i]){
            bark_true_count++;
            temp = temp_vector[i] / bark_size[i];
            amean += temp;
            gmean += log(temp);
        }
    }

    if(amean <= eps) return 0.0;

    gmean = exp(gmean/bark_true_count);
    amean /= bark_true_count;

    return (gmean / amean);

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

    return sqrt(temp) / fq_count;
}

// --- ------------- ---
