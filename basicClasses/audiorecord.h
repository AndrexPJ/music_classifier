#ifndef AUDIORECORD_H
#define AUDIORECORD_H
#include "basicClasses/audiodata.h"



class AudioRecord : public AudioData<double>
{
    public:
    int bitsPerSample;
    AudioRecord();
    AudioRecord(const AudioRecord &record);

};

#endif // AUDIORECORD_H
