#include "boostclassifier.h"

BoostClassifier::BoostClassifier(){
    this->boost = new CvBoost();
}

BoostClassifier::~BoostClassifier(){
    delete this->boost;
}

bool BoostClassifier::train(AudioFeatureExcerpt &excerpt){
    return this->BasicClassifier::train(excerpt);
}


bool BoostClassifier::train(std::vector<std::vector<double> > &train_samples, std::vector<double> &samples_labels){

    cv::Mat labelsMat = this->vectorToMat(samples_labels);
    cv::Mat trainingDataMat = this->vectorToMat(train_samples);
    CvBoostParams params;
    params.boost_type = CvBoost::REAL;
    params.weak_count = 100;
    params.weight_trim_rate = 0.95;
    params.cv_folds = 0;
    params.max_depth = 1;
    cv::Mat mat;
    this->boost->train(trainingDataMat,CV_ROW_SAMPLE,labelsMat,mat,mat,mat,mat,params);
    return true;
}

std::vector<double> BoostClassifier::classify(std::vector<std::vector<double> > &classify_samples){
    std::vector<double> out(classify_samples.size());

    for(int i = 0; i < classify_samples.size(); i++)
        out[i] = this->classify(classify_samples[i]);

    return out;
}

double BoostClassifier::classify(std::vector<double> &classify_sample){
    cv::Mat data = this->vectorToMat(classify_sample);
    return this->boost->predict(data);
}


bool BoostClassifier::save(std::string filename){
    this->boost->save(filename.c_str());
    return true;
}

bool BoostClassifier::load(std::string filename){
    this->boost->load(filename.c_str());
    return true;
}
