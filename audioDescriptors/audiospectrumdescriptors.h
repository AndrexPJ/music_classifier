#ifndef AUDIOSPECTRUMDESCRIPTORS_H
#define AUDIOSPECTRUMDESCRIPTORS_H

#include "audioDescriptors/audiodescriptorextractor.h"
#include "audioTransforms/audiospectrumtransforms.h"
#include "fastFourierTransform/fft.h"

// --- Base Class ---

class AudioSpectrumDescriptorExtractor : public AudioDescriptorExtractor{
protected:
    AudioSpectrum<double> spectrum;
    int result_count;

    virtual double extractForOneFrame(int channel_number ,int frame_number) = 0;
    virtual std::vector<double> getAverageValues(std::vector< std::vector<double> > &channels_values, int result_frames_count);

public:
    AudioSpectrumDescriptorExtractor(AudioSpectrum<double> &spectrum, int result_count = 1);
    std::vector<double> extract();

};
// --- ---------- ---



class SpCentroidDescriptorExtractor : public AudioSpectrumDescriptorExtractor{
protected:
    virtual double extractForOneFrame(int channel_number, int frame_number);
public:
    SpCentroidDescriptorExtractor(AudioSpectrum<double> &spectrum, int result_frames_count = 8);
};


class SpFlatnessDescriptorExtractor : public AudioSpectrumDescriptorExtractor{
protected:
    virtual double extractForOneFrame(int channel_number, int frame_number);
public:
    SpFlatnessDescriptorExtractor(AudioSpectrum<double> &spectrum, int result_frames_count = 8);
};


class SpFluxDescriptorExtractor : public AudioSpectrumDescriptorExtractor{
protected:
    virtual double extractForOneFrame(int channel_number, int frame_number);
public:
    SpFluxDescriptorExtractor(AudioSpectrum<double> &spectrum, int result_frames_count = 8);
};

class SpRollOffDescriptorExtractor : public AudioSpectrumDescriptorExtractor{
private:
    double threshold;
protected:
    virtual double extractForOneFrame(int channel_number, int frame_number);
public:
    SpRollOffDescriptorExtractor(AudioSpectrum<double> &spectrum, int result_frames_count = 8, double threshold = 0.85);
};

class MFCCDescriptorExtractor : public AudioDescriptorExtractor{
private:
    int mfcc_count;
    AudioSpectrum<double> spectrum;
    std::vector< std::vector<double> > filters;
    std::vector<double> extractForOneFrame(int channel_number, int frame_number);
    std::vector<double> getAverageValues(std::vector<std::vector<std::vector<double> > > &channels_values);
public:
    MFCCDescriptorExtractor(AudioSpectrum<double> &spectrum, int mfcc_count = 32);
    std::vector<double> extract();
};

class HistogramDescriptorExtractor : public AudioDescriptorExtractor{
private:
    AudioSpectrum<double> spectrum;

public:
    HistogramDescriptorExtractor(AudioSpectrum<double> &spectrum);
    std::vector<double> extract();
};

#endif // AUDIOSPECTRUMDESCRIPTORS_H
