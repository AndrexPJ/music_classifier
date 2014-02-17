#ifndef AUDIOSPECTRUMTRANSFORMS_H
#define AUDIOSPECTRUMTRANSFORMS_H

#include "basicClasses/audiospectrum.h"
#include "basicClasses/audioampspectrum.h"

#include <vector>

namespace AudioSpectrumTransforms{
   AudioAmpSpectrum getAmpSpectrum(AudioSpectrum<complex> &spectrum);
}

namespace AudioSpectrumTools {
    int getCriticalBandRate(double frequency);
    double frequencyToMel(double frequency);
    double melToFrequency(double mel);

    std::vector< std::vector<double> > getMelFilterbank(int frequency_count, double max_frequency, double min_frequency = 300, int filters_count = 26);
}
#endif // AUDIOSPECTRUMTRANSFORMS_H
