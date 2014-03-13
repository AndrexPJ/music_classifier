#ifndef AUDIOWAVELETTRANSFORMS_H
#define AUDIOWAVELETTRANSFORMS_H

#include "basicClasses/audiowaveletimage.h"
#include "basicClasses/audiorecord.h"
#include <algorithm>

namespace AudioWaveletImageTransforms {
    bool performFullWaveRectification(AudioWaveletImage &image);
    bool performLowPassFiltering(AudioWaveletImage &image, double alpha = 0.9);
    bool perfromDownsampling(AudioWaveletImage &image, int down_sampling_koeff = 16);
    bool performNoiseRemoval(AudioWaveletImage &image);

    AudioData<double> performSummation(AudioWaveletImage &image);
}

#endif // AUDIOWAVELETTRANSFORMS_H
