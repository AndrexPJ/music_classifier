#include "genreclassificator.h"

GenreClassificator::GenreClassificator(BasicClassifier *classifier, AudioFeatureSamplesExtractor *feature_extractor, vector<string> feature_names, string genre){
    this->genre = genre;
    this->classifier = classifier;
    this->feature_extractor = feature_extractor;
    this->feature_names = feature_names;
}

GenreClassificator::~GenreClassificator(){
    delete this->feature_extractor;
    delete this->classifier;
}

double GenreClassificator::classify(string file_name){
    vector<double> features = this->feature_extractor->extract(file_name,this->feature_names);
    return this->classify(features);
}

double GenreClassificator::classify(std::vector<double> &features){
    return this->classifier->classify(features);
}

std::vector<string> GenreClassificator::getFeatureNames(){
    return this->feature_names;
}

string GenreClassificator::getGenreName(){
    return this->genre;
}

GenreClassificator* GenreClassificatorFactory::getGenreClassificator(string genre){
    std::string path = "./svm_classifiers/";

    string *features;
    int features_size;

    //{"classical","metal","jazz","blues","reggae","hiphop","pop","rock","country","disco"};
    // {"PITCHHISTO","MFCC","BEATHISTO","ENERGY","ZCR","SPCENTROID","SPROLLOFF","SPFLATNESS","SPFLUX"};
    if(genre == "classical"){
       features_size = 3;
       features = new string[features_size];

       features[0] = "MFCC";
       features[1] = "SPROLLOFF";
       features[2] = "ENERGY";
    }
    else if(genre == "metal"){
        features_size = 3;
        features = new string[features_size];

        features[0] = "MFCC";
        features[1] = "SPFLUX";
        features[2] = "PITCHHISTO";
    }
    else if(genre == "jazz"){
        features_size = 4;
        features = new string[features_size];

        features[0] = "MFCC";
        features[1] = "SPCENTROID";
        features[2] = "ENERGY";
        features[3] = "ZCR";
    }
    else if(genre == "blues"){
        features_size = 4;
        features = new string[features_size];

        features[0] = "MFCC";
        features[1] = "SPFLUX";
        features[2] = "ZCR";
        features[3] = "SPFLATNESS";
    }
    else if(genre == "reggae"){
        features_size = 5;
        features = new string[features_size];

        features[0] = "MFCC";
        features[1] = "SPFLUX";
        features[2] = "BEATHISTO";
        features[3] = "SPCENTROID";
        features[4] = "ENERGY";
    }
    else if(genre == "hiphop"){
        features_size = 5;
        features = new string[features_size];

        features[0] = "MFCC";
        features[1] = "PITCHHISTO";
        features[2] = "BEATHISTO";
        features[3] = "SPROLLOFF";
        features[4] = "ENERGY";
    }
    else if(genre == "pop"){
        features_size = 5;
        features = new string[features_size];

        features[0] = "MFCC";
        features[1] = "PITCHHISTO";
        features[2] = "SPCENTROID";
        features[3] = "SPFLUX";
        features[4] = "SPROLLOFF";
    }
    else if(genre == "rock"){
        features_size = 4;
        features = new string[features_size];

        features[0] = "MFCC";
        features[1] = "SPFLATNESS";
        features[2] = "PITCHHISTO";
        features[3] = "ZCR";
    }
    else if(genre == "country"){
        features_size = 3;
        features = new string[features_size];

        features[0] = "MFCC";
        features[1] = "SPFLUX";
        features[2] = "ZCR";
    }
    else if(genre == "disco"){
        features_size = 6;
        features = new string[features_size];

        features[0] = "MFCC";
        features[1] = "PITCHHISTO";
        features[2] = "ZCR";
        features[3] = "BEATHISTO";
        features[4] = "SPROLLOFF";
        features[5] = "ENERGY";
    }
    else {
        throw invalid_argument("Bad genre name!");
    }


    SVMClassifier *classifier = new SVMClassifier();
    classifier->load(path + genre);

    vector<string> v_features(features,features + features_size);

    AudioFeatureSamplesExtractor *feature_extractor = new AudioFeatureSamplesExtractor();


    return new GenreClassificator(classifier,feature_extractor,v_features, genre);

}

MultipleGenresClassificator::MultipleGenresClassificator(std::vector<GenreClassificator *> classifiers){
    this->classifiers = classifiers;
}


MultipleGenresClassificator::~MultipleGenresClassificator(){
    for(std::vector<GenreClassificator *>::iterator it = this->classifiers.begin(); it != this->classifiers.end(); it++)
        delete (*it);
}


std::vector<double> MultipleGenresClassificator::getGenreHistogram(string file_name){
    std::vector<double> result;
    for(std::vector<GenreClassificator *>::iterator it = this->classifiers.begin(); it != this->classifiers.end(); it++)
        result.push_back((*it)->classify(file_name));

    return result;
}



MultipleGenresClassificator* MultipleGenresClassificatorFactory::getMultipleGenreClassificator(){
    string genres[] = {"classical","metal","jazz","blues","reggae","hiphop","pop","rock","country","disco"};
    int size = 10;

    std::vector<GenreClassificator*> classifiers(size);

    for(int i = 0; i < 10; i++){
        classifiers[i] = GenreClassificatorFactory::getGenreClassificator(genres[i]);
    }

    return new MultipleGenresClassificator(classifiers);
}

