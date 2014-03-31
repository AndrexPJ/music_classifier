#ifndef AUDIODESCRIPTORCOLLECTORFACTORY_H
#define AUDIODESCRIPTORCOLLECTORFACTORY_H



#define ZCR_NAME "ZCR"
#define ENERGY_NAME "Energy"
#define SPFLUX_NAME "SpFlux"
#define SPFLATNESS_NAME "SpFlatness"
#define SPCENTROID_NAME "SpCentroid"
#define SPROLLOFF_NAME  "SpRollOff"
#define BEATHISTO_NAME  "BeatHistogram"
#define PITCHHISTO_NAME "PitchHistogram"
#define MFCC_NAME "MFCC"


#include "audioDescriptors/audiodescriptorextractor.h"

#include "audioDescriptors/audiorecorddescriptors.h"
#include "audioDescriptors/audiorhythmdescriptors.h"
#include "audioDescriptors/audiospectrumdescriptors.h"
#include "audioDescriptors/audiotonalitydescriptors.h"

#include "audioTransforms/audiowfft.h"
#include "audioTransforms/audiorecordtransforms.h"
#include "audioTransforms/audiospectrumtransforms.h"

#include <string>
#include <iterator>


class AudioDescriptorCollectorFactory{
public:
    static AudioDescriptorCollector getDescriptorCollector(AudioRecord &ar,std::vector<std::string> &extractors_names, int de_result_size = 1);
    static AudioDescriptorCollector getDescriptorCollector(AudioRecord &ar,std::string extractors_names[], int names_count, int de_result_size = 1);
};

#endif // AUDIODESCRIPTORCOLLECTORFACTORY_H
