#include "basicclassifier.h"

BasicClassifier::BasicClassifier(){}

BasicClassifier::~BasicClassifier(){}

bool BasicClassifier::train(AudioFeatureExcerpt &excerpt){
    std::vector<std::vector<double> > features = excerpt.getFeatureSamples();
    std::vector<double> labels = excerpt.getLabels();
    return this->train(features,labels);
}

/*bool BasicClassifier::train(std::vector<std::vector<double> > &train_samples, std::vector<double> &samples_labels){
    return false;
}*/

double BasicClassifier::test(AudioFeatureExcerpt &test_excerpt){
    std::vector<std::vector<double> > features = test_excerpt.getFeatureSamples();
    std::vector<double> labels = test_excerpt.getLabels();

    double bad_answers = 0.0;
    double temp_result;
    for(int i = 0; i < features.size(); i++){
        temp_result = this->classify(features[i]);
        //std::cout << i << " " << temp_result << " " << labels[i] << std::endl;
        if(temp_result != labels[i])
            bad_answers += 1.0;
    }

    return (1.0 - (bad_answers / features.size()));
}

cv::Mat BasicClassifier::vectorToMat(std::vector<double> &vector){
    int size = vector.size();
    cv::Mat data(size,1,CV_32FC1);
    for(int i = 0; i < size; i++)
        data.at<float>(i) = (float)vector[i];
    return data;
}

cv::Mat BasicClassifier::vectorToMat(std::vector<std::vector<double> > &vector){
    int main_size = vector.size();
    if(main_size < 1) return cv::Mat();
    int sub_size = vector[0].size();

    cv::Mat data(main_size, sub_size, CV_32FC1);

    for(int i = 0; i < main_size; i++){
        for(int j = 0; j < sub_size; j++)
            data.at<float>(i,j) = (float)vector[i][j];
    }

    return data;
}
