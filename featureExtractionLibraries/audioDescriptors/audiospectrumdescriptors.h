#ifndef AUDIOSPECTRUMDESCRIPTORS_H
#define AUDIOSPECTRUMDESCRIPTORS_H

#include "featureExtractionLibraries/audioDescriptors/audiodescriptorextractor.h"
#include "featureExtractionLibraries/audioTransforms/audiospectrumtransforms.h"
#include "featureExtractionLibraries/fastFourierTransform/fft.h"

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
    SpCentroidDescriptorExtractor(AudioSpectrum<double> &spectrum, int result_frames_count = 2);
    AudioDescriptorExtractor* clone();
};


class SpFlatnessDescriptorExtractor : public AudioSpectrumDescriptorExtractor{
protected:
    virtual double extractForOneFrame(int channel_number, int frame_number);
public:
    SpFlatnessDescriptorExtractor(AudioSpectrum<double> &spectrum, int result_frames_count = 2);
    AudioDescriptorExtractor* clone();
};


class SpFluxDescriptorExtractor : public AudioSpectrumDescriptorExtractor{
protected:
    virtual double extractForOneFrame(int channel_number, int frame_number);
public:
    SpFluxDescriptorExtractor(AudioSpectrum<double> &spectrum, int result_frames_count = 2);
    AudioDescriptorExtractor* clone() ;
};

class SpRollOffDescriptorExtractor : public AudioSpectrumDescriptorExtractor{
private:
    double threshold;
protected:
    virtual double extractForOneFrame(int channel_number, int frame_number);
public:
    SpRollOffDescriptorExtractor(AudioSpectrum<double> &spectrum, int result_frames_count = 2, double threshold = 0.85);
    AudioDescriptorExtractor* clone();
};

class MFCCDescriptorExtractor : public AudioDescriptorExtractor{
private:
    int mfcc_count;
    AudioSpectrum<double> spectrum;
    std::vector< std::vector<double> > filters;
    std::vector<double> extractForOneFrame(int channel_number, int frame_number);
    std::vector<double> getAverageValues(std::vector<std::vector<std::vector<double> > > &channels_values);
public:
    MFCCDescriptorExtractor(AudioSpectrum<double> &spectrum, int mfcc_count = 26);
    std::vector<double> extract();
    AudioDescriptorExtractor* clone();
};

class HistogramDescriptorExtractor : public AudioDescriptorExtractor{
private:
    AudioSpectrum<double> spectrum;

public:
    HistogramDescriptorExtractor(AudioSpectrum<double> &spectrum);
    HistogramDescriptorExtractor();
    std::vector<double> extract();
    AudioDescriptorExtractor* clone();
};

class MainTicksDescriptorExtractor : public HistogramDescriptorExtractor {
protected:
    int ticks_count;
    bool mode; // result = [[amp],[n]] (true) or [n] (false)
    std::vector<double> histogram;
public:
    MainTicksDescriptorExtractor(AudioSpectrum<double> &spectrum, int ticks_count = 1, bool mode = true);
    MainTicksDescriptorExtractor(std::vector<double> &histogram, int ticks_count = 1, bool mode = true);
    MainTicksDescriptorExtractor(int ticks_count, bool mode = true);
    bool setHistogram(std::vector<double> &histogram);
    std::vector<double> extract();
    AudioDescriptorExtractor* clone();
};



#endif // AUDIOSPECTRUMDESCRIPTORS_H
