#ifndef AUDIOWAVELETIMAGE_H
#define AUDIOWAVELETIMAGE_H

#include "basicClasses/audiodata.h"
#include <math.h>
class AudioWaveletImage : public AudioData<double>
{
private:
    int levelsCount;

    bool checkAvailability(int channel,int level, int number) const;
public:
    AudioWaveletImage();
    AudioWaveletImage(const std::vector< std::vector<double> > &wavelet_raw_data);

    int getLevelsCount() const ;
    int getLevelSize(int level) const ;
    int getChannelsCount() const ;

    double get(int channel, int number, int level) const;
    bool set(int channel, int number, double value, int level);

    //double get(int channel, int number) const;
    //bool set(int channel, int number, double value);


};

#endif // AUDIOWAVELETIMAGE_H
