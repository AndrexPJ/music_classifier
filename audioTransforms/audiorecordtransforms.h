#ifndef AUDIORECORDTRANSFORMS_H
#define AUDIORECORDTRANSFORMS_H

#include "audiorecord.h"
#include "tools.h"
#include <vector>
#include <math.h>
#include <algorithm>
#include <functional>
#include <iostream>

namespace AudioRecordTransforms {

    AudioRecord sizeToPowerOfTwo(const AudioRecord &record, int &out_prefix_size, int &out_suffix_size);
    AudioRecord performPreEmphasisFilter(const AudioRecord &record, double koefficient);
    AudioRecord performHighPassFilter(const AudioRecord &record, double cut_off);
    AudioRecord performLowPassFilter(const AudioRecord &record, double cut_off);
    AudioRecord performDCRemoval(const AudioRecord &record);
    AudioRecord performDownSampling(const AudioRecord &record, int down_sampling_koeff = 16);
    AudioRecord performNormalization(const AudioRecord &record);
}

#endif // AUDIORECORDTRANSFORMS_H
