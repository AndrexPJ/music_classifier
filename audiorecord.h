#ifndef AUDIORECORD_H
#define AUDIORECORD_H
#include <vector>

class AudioRecord
{
    public:
    int sampleRate, channelsCount, bitsPerSample, channelDataSize;
    std::vector< std::vector<double> > channelsData;
    AudioRecord();
    AudioRecord(const AudioRecord &record);
};

#endif // AUDIORECORD_H
