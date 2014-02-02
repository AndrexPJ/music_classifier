#ifndef AUDIORECORDTRANSFORMS_H
#define AUDIORECORDTRANSFORMS_H

#include "audiorecord.h"
#include "tools.h"
#include <vector>
#include <iostream>

namespace AudioRecordTransforms {

class sizingToPowerOfTwo{
public:
    static AudioRecord perform(const AudioRecord &record);
};

}
#endif // AUDIORECORDTRANSFORMS_H
