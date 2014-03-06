#ifndef AUDIOWAVELETIMAGE_H
#define AUDIOWAVELETIMAGE_H

#include "basicClasses/audiodata.h"
#include <math.h>
class AudioWaveletImage
{
private:
    int levels_count;
    int channels_count;
    std::vector<std::vector<double> > values;

    bool checkAvailability(int channel,int level, int number);
public:
    AudioWaveletImage();
    AudioWaveletImage(const std::vector< std::vector<double> > &wavelet_raw_data);

    int getLevelsCount();
    int getLevelSize(int level);

    double get(int channel,int level, int number);
    bool set(int channel,int level, int number, double value);

};

#endif // AUDIOWAVELETIMAGE_H
