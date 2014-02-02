#ifndef AUDIOSAVER_H
#define AUDIOSAVER_H


#include "audiorecord.h"
#include <string>

class AudioSaver{
public:
    static void saveAudioRecord(const AudioRecord &record,std::string filename);
};

#endif // AUDIOSAVER_H
