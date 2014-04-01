#ifndef AUDIODESCRIPTOREXTRACTOR_H
#define AUDIODESCRIPTOREXTRACTOR_H

#include "basicClasses/audiorecord.h"
#include "basicClasses/audiospectrum.h"
#include "basicClasses/audioampspectrum.h"

#include <vector>
#include <math.h>
#include <map>
#include "tools.h"

class AudioDescriptorExtractor
{
protected:
    std::vector<double> output_result;
    virtual bool fillResult();
public:
    AudioDescriptorExtractor();
<<<<<<< HEAD
    AudioDescriptorExtractor(const AudioDescriptorExtractor &extractor);
    virtual std::vector<double> extract() const;
=======
    virtual ~AudioDescriptorExtractor();
    virtual std::vector<double> extract() = 0;
>>>>>>> not-tested
};


class AudioDescriptorCollector : AudioDescriptorExtractor{
private:
<<<<<<< HEAD
    std::vector<AudioDescriptorExtractor> de_vector;
=======
    std::vector<AudioDescriptorExtractor*> de_vector;
>>>>>>> not-tested
public:
    AudioDescriptorCollector();
    ~AudioDescriptorCollector();
    bool addDescriptorExtractor(AudioDescriptorExtractor &de);
    virtual std::vector<double> extract();
};


<<<<<<< HEAD
=======
class BaseDescriptorFactory{
protected:
    std::map< std::string,BaseDescriptorFactory*> type_map;
public:
    BaseDescriptorFactory(AudioRecord &ar);
    BaseDescriptorFactory();
    virtual ~BaseDescriptorFactory();
    virtual AudioDescriptorExtractor* getAudioDescriptor(std::string type);
};

>>>>>>> not-tested

#endif // AUDIODESCRIPTOREXTRACTOR_H
