#include "genreclassificationsystem.h"

GenreClassificationSystem::GenreClassificationSystem(){
     std::string raw_genres[] = {"classical","metal","jazz","blues","reggae","hiphop","pop","rock","country","disco"};
     std::string raw_features[] = {"PITCHHISTO","MFCC","BEATHISTO","ENERGY","ZCR","SPCENTROID","SPROLLOFF","SPFLATNESS","SPFLUX"};
     int genres_size = 10;
     int features_size = 9;

     this->feature_names = std::vector<std::string>(raw_features,raw_features + features_size);
     this->genre_names = std::vector<std::string>(raw_genres,raw_genres + genres_size);

     this->genre_classifiers.resize(genres_size);

     for(int i = 0; i < genres_size; i++){
         this->genre_classifiers[i] = CommitteeClassiferFactory::getCommitteeClassifier(this->genre_names[i]);
     }

     this->feature_extractor = new AudioFeatureSamplesExtractor();
}


GenreClassificationSystem::~GenreClassificationSystem(){
    for(std::vector<CommitteeClassifier*>::iterator it = this->genre_classifiers.begin(); it != this->genre_classifiers.end(); it++){
        delete (*it);
    }

    delete this->feature_extractor;
}


std::vector<double> GenreClassificationSystem::getGenreHistogram(string audio_file_path){
    std::vector<double> result;

    double temp_answer;
    double sum = 0.0;
    std::vector<double> features = this->feature_extractor->extract(audio_file_path,this->feature_names);

    for(std::vector<CommitteeClassifier*>::iterator it = this->genre_classifiers.begin(); it != this->genre_classifiers.end(); it++){
        temp_answer = (*it)->classifyPercent(features);
        result.push_back(temp_answer);
        sum += temp_answer;
    }

    for(std::vector<double>::iterator it = result.begin(); it != result.end(); it++)
        (*it) /= sum;

    return result;
}
