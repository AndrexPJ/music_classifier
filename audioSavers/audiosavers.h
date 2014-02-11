#ifndef AUDIOSAVERS_H
#define AUDIOSAVERS_H

#include "audioSavers/audiosaver.h"


#include <math.h>

class WaveAudioSaver : public AudioSaver{
public:
    static bool saveAudioRecord(const AudioRecord &record, std::string filename);
};

#endif // AUDIOSAVERS_H
