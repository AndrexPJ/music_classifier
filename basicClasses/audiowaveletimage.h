#ifndef AUDIOWAVELETIMAGE_H
#define AUDIOWAVELETIMAGE_H

#include "basicClasses/audiodata.h"
#include <math.h>
class AudioWaveletImage : public AudioData<double>
{
private:
    int levelsCount;

    bool checkAvailability(int channel,int level, int number) const;
    int getBound(int level) const;
public:
    AudioWaveletImage();
    AudioWaveletImage(const std::vector< std::vector<double> > &wavelet_raw_data);

    int getLevelsCount() const ;
    bool setLevelsCount(int count);
    int getLevelSize(int level) const ;
    int getChannelsCount() const ;

    double get(int channel, int level, int number) const;
    bool set(int channel,int level, int number, double value);

    double getGlobal(int channel, int level, int number) const; // number from 0 to max lvl length

};



#endif // AUDIOWAVELETIMAGE_H
