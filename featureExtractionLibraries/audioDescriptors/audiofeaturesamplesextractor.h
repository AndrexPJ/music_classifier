#ifndef AUDIOFEATURESAMPLESEXTRACTOR_H
#define AUDIOFEATURESAMPLESEXTRACTOR_H

#include "featureExtractionLibraries/audioDescriptors/audiodescriptorfactory.h"
#include "audioLoaders/waveaudioloader.h"
#include "basicClasses/audiofeatureexcerpt.h"

class AudioFeatureSamplesExtractor{
public:
    AudioFeatureSamplesExtractor();
    std::vector< std::vector<double> > extract(std::vector<std::string> &file_names, std::vector<std::string> &feature_names);
    std::vector<double> extract(std::string &file_name, std::vector<std::string> &feature_names);
};

class AudioSamplesCreator{
private:
    AudioFeatureExcerpt training_excerpt;
    AudioFeatureExcerpt test_excerpt;

public:
    AudioSamplesCreator(std::vector<std::string> &genres, std::vector<double> &labels, std::vector<int> &training_sizes,std::vector<int> &test_sizes,
                                    std::vector<std::string> &feature_names, std::string path = "./../data/dataset/");

    AudioFeatureExcerpt getTrainingExcerpt();
    AudioFeatureExcerpt getTestExcerpt();
};

#endif // AUDIOFEATURESAMPLESEXTRACTOR_H
