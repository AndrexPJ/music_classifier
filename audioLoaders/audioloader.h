#ifndef AUDIOLOADER_H
#define AUDIOLOADER_H


#include "audiorecord.h"
#include "audioExceptions/audioexceptions.h"
#include <string>

class AudioLoader{
public:
    static AudioRecord loadAudioRecord(std::string filename);
};

#endif // AUDIOLOADER_H
