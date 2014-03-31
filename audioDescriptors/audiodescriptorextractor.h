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
protected:
    std::vector<double> output_result;
    virtual bool fillResult();
public:
    AudioDescriptorExtractor();
    AudioDescriptorExtractor(const AudioDescriptorExtractor &extractor);
    std::vector<double> extract() const;
};


class AudioDescriptorCollector : AudioDescriptorExtractor{
private:
    std::vector<AudioDescriptorExtractor> de_vector;
public:
    AudioDescriptorCollector();
    bool addDescriptorExtractor(AudioDescriptorExtractor &de);
    virtual std::vector<double> extract();
};



#endif // AUDIODESCRIPTOREXTRACTOR_H
