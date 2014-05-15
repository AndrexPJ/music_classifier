#include "committeeclassifier.h"



CommitteeClassifier::CommitteeClassifier(std::vector<BasicClassifier *> expert_classifiers){
    this->expert_classifiers = expert_classifiers;
    this->master_classifier = new SVMClassifier();
}


CommitteeClassifier::CommitteeClassifier(BasicClassifier *master_classifier, std::vector<BasicClassifier *> expert_classifiers){
    this->expert_classifiers = expert_classifiers;
    this->master_classifier = master_classifier;
}

CommitteeClassifier::~CommitteeClassifier(){
    for(std::vector<BasicClassifier*>::iterator it = this->expert_classifiers.begin(); it!= this->expert_classifiers.end();it++)
        delete (*it);
    delete this->master_classifier;
}


bool CommitteeClassifier::train(std::vector<std::vector<double> > &train_samples, std::vector<double> &samples_labels){
    std::vector<std::vector<double> > temp_expert_answers;
    temp_expert_answers.resize(train_samples.size());

    for(int i = 0; i < train_samples.size(); i++){
        temp_expert_answers[i] = this->expertsInterview(train_samples[i]);
    }

    return this->master_classifier->train(temp_expert_answers,samples_labels);
}

bool CommitteeClassifier::train(AudioFeatureExcerpt &excerpt){
    return this->BasicClassifier::train(excerpt);
}

double CommitteeClassifier::classifyPercent(std::vector<double> &classify_sample){
    double temp_answer = 0.0;

    std::vector<double> temp_expert_answers = this->expertsInterview(classify_sample);

    for(std::vector<double>::iterator it = temp_expert_answers.begin(); it!= temp_expert_answers.end();it++)
        temp_answer += (*it);

    temp_answer /= temp_expert_answers.size();

    temp_answer = (temp_answer + 1) / 2;

    return temp_answer;

}

double CommitteeClassifier::classify(std::vector<double> &classify_sample){
    std::vector<double> expert_answers = this->expertsInterview(classify_sample);

    return this->master_classifier->classify(expert_answers);
}


std::vector<double> CommitteeClassifier::expertsInterview(std::vector<double> &classify_sample){
    std::vector<double> temp_vector;
    double temp_answer;

    for(std::vector<BasicClassifier*>::iterator it = this->expert_classifiers.begin(); it!= this->expert_classifiers.end();it++){
        temp_answer = (*it)->classify(classify_sample);
        temp_vector.push_back(temp_answer);
    }

    return temp_vector;
}

bool CommitteeClassifier::save(std::string filename){
    return this->master_classifier->save(filename);
}

CommitteeClassifier* CommitteeClassiferFactory::getCommitteeClassifier(std::string genre, std::string master_classifiers_path, std::string expert_classifiers_path){
    std::string genres[] = {"classical","metal","jazz","blues","reggae","hiphop","pop","rock","country","disco"};
    int genres_count = 10;

    std::vector<std::string> v_genres(genres, genres + genres_count);

    int genre_index = std::find(v_genres.begin(),v_genres.end(),genre) - v_genres.begin();

    std::vector<BasicClassifier*> classifiers;
    BoostClassifier *temp_classifier;
    //SVMClassifier *master_classifier = new SVMClassifier();
    //master_classifier->load(master_classifiers_path+genre);

    for(int i = 0; i < genre_index; i++){
        // reverse classifiers loading
        temp_classifier = new BoostClassifier(true);
        temp_classifier->load(expert_classifiers_path+genres[i]+"_"+genre);
        //temp_classifier->load(expert_classifiers_path+genre+"_"+genres[i]);
        classifiers.push_back(temp_classifier);
    }

    for(int i = genre_index + 1; i < genres_count; i++){
      temp_classifier = new BoostClassifier();
      temp_classifier->load(expert_classifiers_path+genre+"_"+genres[i]);
      //temp_classifier->load(expert_classifiers_path+genres[i]+"_"+genre);
      classifiers.push_back(temp_classifier);
    }

    return new CommitteeClassifier(classifiers);
}
