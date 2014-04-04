#ifndef AUDIODWT_H
#define AUDIODWT_H

#include "basicClasses/audiorecord.h"
#include "basicClasses/audiowaveletimage.h"
#include "featureExtractionLibraries/waveletTransform/dwt.h"

class AudioDWT
{
public:
    static bool perform(AudioRecord &record, AudioWaveletImage &result_image);

};

#endif // AUDIODWT_H
