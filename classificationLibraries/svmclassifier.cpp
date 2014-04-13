#include "svmclassifier.h"


SVMClassifier::SVMClassifier(int kernel_type,int svm_type){
    this->params = new CvSVMParams();
    this->params->svm_type    = svm_type;
    this->params->kernel_type = kernel_type;
    this->params->nu = 0.5;
    this->params->degree = 3.0;
   // this->params->term_crit   = cvTermCriteria(CV_TERMCRIT_ITER, 1000, 1e-6);
    this->svm = new CvSVM();
    this->trained = false;
}

SVMClassifier::~SVMClassifier(){
    delete this->svm;
    delete this->params;
    this->trained = false;
}

bool SVMClassifier::train(AudioFeatureExcerpt &excerpt){
    return this->BasicClassifier::train(excerpt);
}

bool SVMClassifier::train(std::vector<std::vector<double> > &train_samples, std::vector<double> &samples_labels){

    cv::Mat labelsMat = this->vectorToMat(samples_labels);
    cv::Mat trainingDataMat = this->vectorToMat(train_samples);

    this->svm->train_auto(trainingDataMat, labelsMat, cv::Mat(), cv::Mat(),*this->params);
    this->trained = true;
    return true;
}


std::vector<double> SVMClassifier::classify(std::vector<std::vector<double> > &classify_samples){
    if(!this->trained) return std::vector<double>();
    std::vector<double> out(classify_samples.size());

    for(int i = 0; i < classify_samples.size(); i++)
        out[i] = this->classify(classify_samples[i]);

    return out;
}

double SVMClassifier::classify(std::vector<double> &classify_sample){
    cv::Mat data = this->vectorToMat(classify_sample);
    return this->svm->predict(data);
}


bool SVMClassifier::save(std::string filename){
    this->svm->save(filename.c_str());
    return true;
}

bool SVMClassifier::load(std::string filename){
    this->svm->load(filename.c_str());
    return true;
}
