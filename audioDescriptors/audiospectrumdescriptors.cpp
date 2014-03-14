#include "audiospectrumdescriptors.h"


// --- Base Class ---
AudioSpectrumDescriptorExtractor::AudioSpectrumDescriptorExtractor(AudioSpectrum<double> &spectrum, int result_count) : AudioDescriptorExtractor(){
    this->spectrum = spectrum;
    if(result_count > spectrum.getChannelDataSize())
        this->result_count = spectrum.getChannelDataSize();
    else
        this->result_count = result_count;

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
SpCentroidDescriptorExtractor::SpCentroidDescriptorExtractor(AudioSpectrum<double> &spectrum, int result_frames_count) : AudioSpectrumDescriptorExtractor(spectrum, result_frames_count){
}


double SpCentroidDescriptorExtractor::extractForOneFrame(int channel_number, int frame_number){
     int fq_count = spectrum.getFrequencyCount();
     double fq_amp_sum = 0.0;
     double amp_sum = 0.0;
     double temp = 0.0;

     for(int fq_i = 0; fq_i < fq_count; fq_i++){
         temp = pow(this->spectrum[channel_number][frame_number][fq_i],2);
         fq_amp_sum += fq_i * temp;
         amp_sum += temp;
     }
     if(amp_sum == 0.0) return 0.0;
     return (fq_amp_sum / (amp_sum * fq_count));
}
// --- ----------------- ---


// --- Spectral Flatness ---
SpFlatnessDescriptorExtractor::SpFlatnessDescriptorExtractor(AudioSpectrum<double> &spectrum, int result_frames_count) : AudioSpectrumDescriptorExtractor(spectrum,result_frames_count){
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

        bark = AudioSpectrumTools::getCriticalBandRate(frequency) - 1;
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
SpFluxDescriptorExtractor::SpFluxDescriptorExtractor(AudioSpectrum<double> &spectrum, int result_frames_count) : AudioSpectrumDescriptorExtractor(spectrum,result_frames_count){
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


// --- Spectral Roll-off ---
SpRollOffDescriptorExtractor::SpRollOffDescriptorExtractor(AudioSpectrum<double> &spectrum, int result_frames_count, double threshold) : AudioSpectrumDescriptorExtractor(spectrum, result_frames_count){
    this->threshold = threshold;
}

double SpRollOffDescriptorExtractor::extractForOneFrame(int channel_number, int frame_number){
    int fq_count = this->spectrum.getFrequencyCount();

    double max_sum = 0.0;
    double temp_sum = 0.0;

    for(int fq_i = 0; fq_i < fq_count; fq_i++)
        max_sum += this->spectrum[channel_number][frame_number][fq_i];
    temp_sum = max_sum;
    max_sum *= this->threshold;

    int result_fq_i;
    for(result_fq_i = fq_count - 1; result_fq_i >= 0; result_fq_i--){
        temp_sum -= this->spectrum[channel_number][frame_number][result_fq_i];
        if(temp_sum < max_sum) break;
    }


    return (double(result_fq_i) / fq_count) ;
    //return this->spectrum.getFrequency(result_fq_i);
}

// --- ----------------- ---


// --- MFCC ---
MFCCDescriptorExtractor::MFCCDescriptorExtractor(AudioSpectrum<double> &spectrum, int mfcc_count) : AudioDescriptorExtractor(){
    this->spectrum = spectrum;
    this->mfcc_count = mfcc_count;
    int fq_count = this->spectrum.getFrequencyCount();
    this->filters = AudioSpectrumTools::getMelFilterbank(fq_count, this->spectrum.getFrequency(fq_count - 1),300,this->mfcc_count);
}


std::vector<double> MFCCDescriptorExtractor::getAverageValues(std::vector<std::vector<std::vector<double> > > &channels_values){
     std::vector<double> result;
     result.resize(this->mfcc_count/2);

     int channels_count = this->spectrum.getChannelsCount();
     int data_size = this->spectrum.getChannelDataSize();

     double temp;
     for(int i = 0; i < this->mfcc_count/2; i++){
         temp = 0.0;
         for(int ch = 0; ch < channels_count; ch++)
             for(int step = 0; step < data_size; step++)
                temp+=channels_values[ch][step][i];
         result[i] = temp / (data_size * channels_count);
     }
     return result;
}

std::vector<double> MFCCDescriptorExtractor::extractForOneFrame(int channel_number, int frame_number){
    std::vector<double> temp_in;
    std::vector<double> result;
    std::vector<complex> temp_out;

    int new_size;

    temp_in.resize(this->mfcc_count);
    result.resize(this->mfcc_count/2);

    int fq_count = this->spectrum.getFrequencyCount();
    double temp;

    for(int i = 0; i < this->mfcc_count; i++){
        temp = 0.0;
        for(int fq_i = 0; fq_i < fq_count; fq_i++)
            temp += this->spectrum[channel_number][frame_number][fq_i] * this->filters[i][fq_i];
        if(temp == 0.0)
            temp_in[i] = 0.0;
        else
            temp_in[i] = log10(temp * temp);
    }

    if(this->mfcc_count & (this->mfcc_count - 1)){
        new_size = Tools::nearestPowerOfTwoAbove(this->mfcc_count);

        for(int i = 0; i < (new_size - this->mfcc_count); i++)
            temp_in.push_back(0.0);

        temp_out.resize(new_size);
    }

    FFT::Inverse(temp_in,temp_out);

    for(int i = 0; i < this->mfcc_count/2; i++)
        result[i] = temp_out[i].norm();

    return result;
}

std::vector<double> MFCCDescriptorExtractor::extract(){

    std::vector < std::vector< std::vector<double> > > channels_values;

    int channels_count = this->spectrum.getChannelsCount();
    int frames_count = this->spectrum.getChannelDataSize();

    channels_values.resize(channels_count);

    for(int i = 0; i < channels_count; i++){
        channels_values[i].resize(frames_count);
        for(int j = 0; j < frames_count; j++)
            channels_values[i][j] = this->extractForOneFrame(i,j);
    }

    return this->getAverageValues(channels_values);
}

// --- ---- ---

HistogramDescriptorExtractor::HistogramDescriptorExtractor(){

}

HistogramDescriptorExtractor::HistogramDescriptorExtractor(AudioSpectrum<double> &spectrum){
    this->spectrum = spectrum;
}

std::vector<double> HistogramDescriptorExtractor::extract(){
    int frequency_count = this->spectrum.getFrequencyCount();
    int data_size = this->spectrum.getChannelDataSize();
    int channels_count = this->spectrum.getChannelsCount();

    double norm = 0.0;

    std::vector<double> result;
    result.assign(frequency_count,0.0);

    for(int fq_i = 0; fq_i < frequency_count; fq_i++){
        for(int i = 0; i < data_size; i++)
            for(int ch = 0; ch < channels_count; ch++)
                result[fq_i] += this->spectrum[ch][i][fq_i];
        result[fq_i] /= (channels_count * data_size);
        norm += result[fq_i];
    }


    for(int fq_i = 1; fq_i < frequency_count; fq_i++){
        result[fq_i] /= norm;
    }

    return result;

}


MainTicksDescriptorExtractor::MainTicksDescriptorExtractor(AudioSpectrum<double> &spectrum, int ticks_count, bool mode) : HistogramDescriptorExtractor(spectrum){
    this->ticks_count = ticks_count;
    this->histogram = this->HistogramDescriptorExtractor::extract();
    this->mode = mode;
}

MainTicksDescriptorExtractor::MainTicksDescriptorExtractor(std::vector<double> &histogram, int ticks_count, bool mode) {
    this->ticks_count = ticks_count;
    this->histogram = histogram;
    this->mode = mode;
}

MainTicksDescriptorExtractor::MainTicksDescriptorExtractor(int ticks_count, bool mode){
    this->ticks_count = ticks_count;
    this->mode = mode;
}

bool MainTicksDescriptorExtractor::setHistogram(std::vector<double> &histogram){
    this->histogram = histogram;
    return true;
}

std::vector<double> MainTicksDescriptorExtractor::extract(){
    int result_size;
    if(this->mode)
        result_size = this->ticks_count * 2;
    else
        result_size = this->ticks_count;

    std::vector<double> temp = this->histogram;

    if(temp.size() == 0) return temp;

    std::vector<double> result(result_size);

    std::sort(temp.begin(),temp.end());
    std::reverse(temp.begin(),temp.end());

    for(int i = 0; i < this->ticks_count; i++){
        result[i] = double(std::find(this->histogram.begin(),this->histogram.end(),temp[i]) - this->histogram.begin()) / (this->histogram.size() - 1);
        if(this->mode)
            result[i + this->ticks_count] = temp[i];
    }

    return result;

}



