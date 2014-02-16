#ifndef AUDIOSPECTRUMDESCRIPTORS_H
#define AUDIOSPECTRUMDESCRIPTORS_H

#include "audioDescriptors/audiodescriptorextractor.h"
#include "audioTransforms/audiospectrumtransforms.h"

class AudioSpectrumDescriptorExtractor : public AudioDescriptorExtractor{
protected:
    AudioAmpSpectrum spectrum;
    int result_count;

    virtual double extractForOneFrame(int channel_number ,int frame_number) = 0;
    virtual std::vector<double> getAverageValues(std::vector< std::vector<double> > &channels_values, int result_frames_count);
public:
    AudioSpectrumDescriptorExtractor(AudioAmpSpectrum &spectrum, int result_count = 1);
    std::vector<double> extract();

};



class SpCentroidDescriptorExtractor : public AudioSpectrumDescriptorExtractor{
protected:
    virtual double extractForOneFrame(int channel_number, int frame_number);
public:
    SpCentroidDescriptorExtractor(AudioAmpSpectrum &spectrum, int result_frames_count = 8);
};


class SpFlatnessDescriptorExtractor : public AudioSpectrumDescriptorExtractor{
protected:
    virtual double extractForOneFrame(int channel_number, int frame_number);
public:
    SpFlatnessDescriptorExtractor(AudioAmpSpectrum &spectrum, int result_frames_count = 8);
};

class SpFluxDescriptorExtractor : public AudioSpectrumDescriptorExtractor{
protected:
    virtual double extractForOneFrame(int channel_number, int frame_number);
public:
    SpFluxDescriptorExtractor(AudioAmpSpectrum &spectrum, int result_frames_count = 8);
};

#endif // AUDIOSPECTRUMDESCRIPTORS_H
