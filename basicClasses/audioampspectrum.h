#ifndef AUDIOAMPSPECTRUM_H
#define AUDIOAMPSPECTRUM_H

#include "basicClasses/audiospectrum.h"

class AudioAmpSpectrum : public AudioSpectrum<double>
{
public:
    AudioAmpSpectrum();
    AudioAmpSpectrum(const AudioAmpSpectrum &spectrum);
};

#endif // AUDIOAMPSPECTRUM_H
