#ifndef AUDIODESCRIPTOREXTRACTOR_H
#define AUDIODESCRIPTOREXTRACTOR_H

#include "basicClasses/audiorecord.h"
#include "basicClasses/audiospectrum.h"
#include "basicClasses/audioampspectrum.h"

#include <vector>
#include <math.h>
#include <map>
#include "tools/tools.h"

/*class Sample{
public:
    double label;
    std::vector<double> features;

    Sample();
    Sample(std::vector<double> &features, double label);
};*/

class AudioDescriptorExtractor
{
public:
    AudioDescriptorExtractor();
    virtual ~AudioDescriptorExtractor();
    virtual std::vector<double> extract();
    virtual AudioDescriptorExtractor* clone() = 0;
};


class AudioDescriptorCollector : AudioDescriptorExtractor{
private:
    std::vector<AudioDescriptorExtractor*> de_vector;
public:
    AudioDescriptorCollector();
    ~AudioDescriptorCollector();
    bool addDescriptorExtractor(AudioDescriptorExtractor *de);
    virtual std::vector<double> extract();
    AudioDescriptorExtractor* clone();
};


class BaseDescriptorFactory{
protected:
    std::map< std::string,BaseDescriptorFactory*> type_map;
public:
    BaseDescriptorFactory(AudioRecord *ar);
    BaseDescriptorFactory();
    virtual ~BaseDescriptorFactory();
    virtual AudioDescriptorExtractor* getAudioDescriptor(std::string type);
};



#endif // AUDIODESCRIPTOREXTRACTOR_H
