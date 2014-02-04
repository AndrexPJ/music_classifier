#ifndef AUDIORECORDTRANSFORMS_H
#define AUDIORECORDTRANSFORMS_H

#include "audiorecord.h"
#include "tools.h"
#include <vector>
#include <iostream>
#include <math.h>

namespace AudioRecordTransforms {

class SizingToPowerOfTwo{
public:
    static AudioRecord perform(const AudioRecord &record, int &out_prefix_size, int &out_suffix_size);
};


}
#endif // AUDIORECORDTRANSFORMS_H
