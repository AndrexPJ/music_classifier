#include "svmclassifier.h"


SVMClassifier::SVMClassifier(int kernel_type,int svm_type){
    this->params = new CvSVMParams();
    this->params->svm_type    = svm_type;
    this->params->kernel_type = kernel_type;
    this->params->degree = 2.0;
   // this->params->term_crit   = cvTermCriteria(CV_TERMCRIT_ITER, 1000, 1e-6);
    this->svm = new CvSVM();
    this->trained = false;
}

SVMClassifier::~SVMClassifier(){
    delete this->svm;
    delete this->params;
    this->trained = false;
}


bool SVMClassifier::train(std::vector<std::vector<double> > &train_samples, std::vector<double> &samples_labels){
    int train_size = train_samples.size();
    int labels_size = samples_labels.size();

    if(train_size == 0) return false;
    if(train_size != labels_size) return false;

    int features_size = train_samples[0].size();

    for(std::vector<std::vector<double> >::iterator it = train_samples.begin(); it != train_samples.end(); it++)
        if((*it).size() != features_size) return false;



    cv::Mat labelsMat(labels_size, 1, CV_32FC1);
    cv::Mat trainingDataMat(train_size, features_size , CV_32FC1);

    for(int i = 0; i < train_size; i++){
        labelsMat.at<float>(i) = samples_labels[i];
        for(int j = 0; j < features_size; j++)
            trainingDataMat.at<float>(i,j) = train_samples[i][j];
    }


    this->svm->train(trainingDataMat, labelsMat, cv::Mat(), cv::Mat(),*this->params);
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
    int size = classify_sample.size();
    cv::Mat data(size,1,CV_32FC1);

    for(int i = 0; i < size; i++)
        data.at<float>(i) = classify_sample[i];

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
