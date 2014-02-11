#ifndef AUDIOSAVER_H
#define AUDIOSAVER_H


#include "audiorecord.h"
#include "audioExceptions/audioexceptions.h"
#include <string>
#include <fstream>

class AudioSaver{
public:
    static bool saveAudioRecord(const AudioRecord &record,std::string filename);
};

#endif // AUDIOSAVER_H
