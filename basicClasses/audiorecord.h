#ifndef AUDIORECORD_H
#define AUDIORECORD_H
#include "basicClasses/audiodata.h"



class AudioRecord : public AudioData<double>
{
protected:
    int bitsPerSample;
public:
    AudioRecord();
    AudioRecord(const AudioRecord &record);
    int getBitsPerSample() const;
    bool setBitsPerSample(int bps);

};

#endif // AUDIORECORD_H
