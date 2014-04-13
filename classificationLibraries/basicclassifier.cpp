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

std::pair<double,double> BasicClassifier::test(AudioFeatureExcerpt &test_excerpt){
    std::vector<std::vector<double> > features = test_excerpt.getFeatureSamples();
    std::vector<double> labels = test_excerpt.getLabels();

    std::pair<double,double> result;

    double bad_answers_pos_class = 0.0;
    int pos_class_size = 0;
    double bad_answers_neg_class = 0.0;
    int neg_class_size = 0;

    for(int i = 0; i < features.size(); i++){
        if(labels[i] == 1.0){
            if(this->classify(features[i]) != labels[i])
                bad_answers_pos_class += 1.0;
            pos_class_size++;
        }
        if(labels[i] == -1.0){
            if(this->classify(features[i]) != labels[i])
                bad_answers_neg_class += 1.0;
            neg_class_size++;
        }
    }

    result.first = 1.0 - bad_answers_pos_class/pos_class_size;
    result.second = 1.0 - bad_answers_neg_class/neg_class_size;

    return result;
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
