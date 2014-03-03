#ifndef AUDIOAMPSPECTRUM_H
#define AUDIOAMPSPECTRUM_H

#include "basicClasses/audiospectrum.h"

class AudioAmpSpectrum : public AudioSpectrum<double>
{
public:
    AudioAmpSpectrum();
    AudioAmpSpectrum(const AudioAmpSpectrum &spectrum);
};


class AudioPitchChroma : public AudioSpectrum<double>{
public:
    AudioPitchChroma();
    AudioPitchChroma(const AudioPitchChroma &pitch_chroma);

};
#endif // AUDIOAMPSPECTRUM_H
