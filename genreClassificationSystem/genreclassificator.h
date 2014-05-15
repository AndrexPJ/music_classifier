#ifndef GENRECLASSIFICATOR_H
#define GENRECLASSIFICATOR_H

#include <string>
#include <vector>
#include "featureExtractionLibraries/audioDescriptors/audiofeaturesamplesextractor.h"
#include "classificationLibraries/basicclassifier.h"
#include "classificationLibraries/svmclassifier.h"

class GenreClassificator{
private:
    std::vector<string> feature_names;
    AudioFeatureSamplesExtractor *feature_extractor;
    string genre;
    BasicClassifier *classifier;
public:
    GenreClassificator(BasicClassifier *classifier, AudioFeatureSamplesExtractor *feature_extractor, vector<string> feature_names,string genre);
    ~GenreClassificator();
    double classify(string file_name);
    double classify(std::vector<double> &features);
    std::vector<string> getFeatureNames();
    string getGenreName();
};


class MultipleGenresClassificator{
private:
    std::vector<GenreClassificator*> classifiers;
public:
    MultipleGenresClassificator(std::vector<GenreClassificator*> classifiers);
    ~MultipleGenresClassificator();
    std::vector<double> getGenreHistogram(string file_name);
};

class GenreClassificatorFactory{
public:
    static GenreClassificator* getGenreClassificator(std::string genre);

};


class MultipleGenresClassificatorFactory{
public:
    static MultipleGenresClassificator* getMultipleGenreClassificator();
};

#endif // GENRECLASSIFICATOR_H
