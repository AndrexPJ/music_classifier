#ifndef AUDIORECORDTRANSFORMS_H
#define AUDIORECORDTRANSFORMS_H

#include "audiorecord.h"
#include "tools.h"
#include <vector>
#include <math.h>

namespace AudioRecordTransforms {

    AudioRecord sizeToPowerOfTwo(const AudioRecord &record, int &out_prefix_size, int &out_suffix_size);
}

#endif // AUDIORECORDTRANSFORMS_H
