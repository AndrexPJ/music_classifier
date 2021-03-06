#ifndef AUDIOWFFT_H
#define AUDIOWFFT_H

#include "basicClasses/audiorecord.h"
#include "basicClasses/audiospectrum.h"
#include "featureExtractionLibraries/fastFourierTransform/wfft.h"

class AudioWFFT
{
public:
    static bool perform(AudioRecord &in_record, AudioSpectrum<complex> &out_spectrum,WindowFunction &wf, int hop_size, int channels_count = 0);
};



#endif // AUDIOWFFT_H
