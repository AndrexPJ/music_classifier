#ifndef AUDIOSPECTRUMDESCRIPTORS_H
#define AUDIOSPECTRUMDESCRIPTORS_H

#include "audioDescriptors/audiodescriptorextractor.h"
#include "audioTransforms/audiospectrumtransforms.h"

// --- Base Class ---
template <class T> // T is result for one frame
class AudioSpectrumDescriptorExtractor : public AudioDescriptorExtractor{
protected:
    AudioAmpSpectrum spectrum;
    int result_count;

    virtual T extractForOneFrame(int channel_number ,int frame_number) = 0;
    std::vector<T> getAverageValues(std::vector< std::vector<T> > &channels_values, int result_frames_count);
    std::vector< std::vector<double> > getAverageValues(std::vector< std::vector< std::vector<double> > > &channels_values, int result_frames_count);

public:
    AudioSpectrumDescriptorExtractor(AudioAmpSpectrum &spectrum, int result_count = 1);
    std::vector<double> extract();

};

template <class T>
AudioSpectrumDescriptorExtractor<T>::AudioSpectrumDescriptorExtractor(AudioAmpSpectrum &spectrum, int result_count) : AudioDescriptorExtractor(){
    this->spectrum = spectrum;
    if(result_count > spectrum.getChannelDataSize())
        this->result_count = spectrum.getChannelDataSize();
    else
        this->result_count = result_count;
;
}

template <class T>
std::vector<T> AudioSpectrumDescriptorExtractor<T>::getAverageValues(std::vector< std::vector<T> > &channels_values, int result_frames_count){
    std::vector<T> result_values;
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


template <class T>
std::vector<double> AudioSpectrumDescriptorExtractor<T>::extract(){
    std::vector < std::vector<T> > channels_values;

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




class SpCentroidDescriptorExtractor : public AudioSpectrumDescriptorExtractor<double>{
protected:
    virtual double extractForOneFrame(int channel_number, int frame_number);
public:
    SpCentroidDescriptorExtractor(AudioAmpSpectrum &spectrum, int result_frames_count = 8);
};


class SpFlatnessDescriptorExtractor : public AudioSpectrumDescriptorExtractor<double>{
protected:
    virtual double extractForOneFrame(int channel_number, int frame_number);
public:
    SpFlatnessDescriptorExtractor(AudioAmpSpectrum &spectrum, int result_frames_count = 8);
};


class SpFluxDescriptorExtractor : public AudioSpectrumDescriptorExtractor<double>{
protected:
    virtual double extractForOneFrame(int channel_number, int frame_number);
public:
    SpFluxDescriptorExtractor(AudioAmpSpectrum &spectrum, int result_frames_count = 8);
};

class SpRollOffDescriptorExtractor : public AudioSpectrumDescriptorExtractor<double>{
private:
    double threshold;
protected:
    virtual double extractForOneFrame(int channel_number, int frame_number);
public:
    SpRollOffDescriptorExtractor(AudioAmpSpectrum &spectrum, int result_frames_count = 8, double threshold = 0.85);
};

#endif // AUDIOSPECTRUMDESCRIPTORS_H
