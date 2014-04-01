#ifndef AUDIOSPECTRUMTRANSFORMS_H
#define AUDIOSPECTRUMTRANSFORMS_H

#include "basicClasses/audiospectrum.h"
#include "basicClasses/audioampspectrum.h"
#include "specialFunctions/correlationfunctions.h"
#include "tools.h"
#include <vector>


namespace AudioSpectrumTransforms{
   AudioAmpSpectrum getAmpSpectrum(AudioSpectrum<complex> &spectrum);
   AudioPhaseSpectrum getPhaseSpectrum(AudioSpectrum<complex> &spectrum);
   AudioAmpSpectrum getLogAmpSpectrum(AudioSpectrum<double> &spectrum);
   AudioPitchChroma getPitchChroma(AudioSpectrum<double> &spectrum);
   AudioBeatSpectrum getBeatSpectrum(AudioSpectrum<double> &spectrum);


}

namespace AudioSpectrumTools {
    int getCriticalBandRate(double frequency);
    double frequencyToMel(double frequency);
    double melToFrequency(double mel);

    std::vector< std::vector<double> > getMelFilterbank(int frequency_count, double max_frequency, double min_frequency = 300, int filters_count = 26);
    std::vector< std::vector<double> > getSemiToneFilterbank(int frequency_count, double max_frequency , double mid_frequency = 261.63, int octaves_count = 4);

}
#endif // AUDIOSPECTRUMTRANSFORMS_H
