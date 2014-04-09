#ifndef AUDIOFEATURESAMPLESEXTRACTOR_H
#define AUDIOFEATURESAMPLESEXTRACTOR_H

#include "featureExtractionLibraries/audioDescriptors/audiodescriptorfactory.h"
#include "audioLoaders/waveaudioloader.h"
#include "basicClasses/audiofeatureexcerpt.h"

class AudioFeatureSamplesExtractor{
public:
    AudioFeatureSamplesExtractor();
    std::vector< std::vector<double> > extract(std::vector<std::string> &file_names, std::vector<std::string> &feature_names);
};

class AudioSamplesCreator{
private:
    std::vector<std::vector<double> > training_samples;
    std::vector<std::vector<double> > test_samples;
    std::vector<double> training_labels;
    std::vector<double> test_labels;
public:
    AudioSamplesCreator(std::vector<std::string> &genres, std::vector<double> &labels, std::vector<int> &training_sizes,std::vector<int> &test_sizes,
                                    std::vector<std::string> &feature_names, std::string path = "./../data/dataset/");

    AudioFeatureExcerpt getTrainingExcerpt();
    AudioFeatureExcerpt getTestExcerpt();
};

#endif // AUDIOFEATURESAMPLESEXTRACTOR_H
