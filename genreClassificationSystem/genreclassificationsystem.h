#ifndef GENRECLASSIFICATIONSYSTEM_H
#define GENRECLASSIFICATIONSYSTEM_H

#include "featureExtractionLibraries/audioDescriptors/audiofeaturesamplesextractor.h"
#include "classificationLibraries/committeeclassifier.h"

class GenreClassificationSystem
{
private:
    std::vector<std::string> feature_names;
    std::vector<std::string> genre_names;
    AudioFeatureSamplesExtractor *feature_extractor;
    std::vector<CommitteeClassifier*> genre_classifiers;
public:
    GenreClassificationSystem();
    ~GenreClassificationSystem();

    std::vector<double> getGenreHistogram(std::string audio_file_path);
};

#endif // GENRECLASSIFICATIONSYSTEM_H
