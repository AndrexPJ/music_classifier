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


class AudioBeatSpectrum : public AudioSpectrum<double>{
public:
    AudioBeatSpectrum();
    AudioBeatSpectrum(const AudioBeatSpectrum &spectrum);
};

class AudioPhaseSpectrum : public AudioSpectrum<double>{
public:
    AudioPhaseSpectrum();
    AudioPhaseSpectrum(const AudioPhaseSpectrum &spectrum);
};
#endif // AUDIOAMPSPECTRUM_H
