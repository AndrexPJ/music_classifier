#ifndef AUDIORECORDTRANSFORMS_H
#define AUDIORECORDTRANSFORMS_H

#include "audiorecord.h"
#include "tools.h"
#include <vector>
#include <math.h>

namespace AudioRecordTransforms {

    AudioRecord sizeToPowerOfTwo(const AudioRecord &record, int &out_prefix_size, int &out_suffix_size);
    AudioRecord performPreEmphasisFilter(const AudioRecord &record, double koefficient);
    AudioRecord performHighPassFilter(const AudioRecord &record, double cut_off);
    AudioRecord performLowPassFilter(const AudioRecord &record, double cut_off);
    AudioRecord performDCRemoval(const AudioRecord &record);
}

#endif // AUDIORECORDTRANSFORMS_H
