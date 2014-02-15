#ifndef AUDIODESCRIPTOREXTRACTOR_H
#define AUDIODESCRIPTOREXTRACTOR_H

#include "basicClasses/audiorecord.h"
#include "basicClasses/audiospectrum.h"
#include "basicClasses/audioampspectrum.h"


#include <vector>
#include <math.h>
#include "tools.h"

class AudioDescriptorExtractor
{
public:
    AudioDescriptorExtractor();
    virtual std::vector<double> extract() = 0;
};


#endif // AUDIODESCRIPTOREXTRACTOR_H
