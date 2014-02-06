#ifndef AUDIOWFFT_H
#define AUDIOWFFT_H

#include "basicClasses/audiorecord.h"
#include "basicClasses/audiospectrum.h"
#include "fastFourierTransform/wfft.h"

class AudioWFFT
{
public:
    static bool perform(AudioRecord &in_record, AudioSpectrum<complex> &out_spectrum,int window_size, int hop_size, int channels_count = 0);
};

#endif // AUDIOWFFT_H
