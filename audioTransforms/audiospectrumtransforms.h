#ifndef AUDIOSPECTRUMTRANSFORMS_H
#define AUDIOSPECTRUMTRANSFORMS_H

#include "basicClasses/audiospectrum.h"
#include "basicClasses/audioampspectrum.h"


namespace AudioSpectrumTransforms{

   AudioAmpSpectrum getAmpSpectrum(AudioSpectrum<complex> &spectrum);

   int getCriticalBandRate(double frequency);

}

#endif // AUDIOSPECTRUMTRANSFORMS_H
