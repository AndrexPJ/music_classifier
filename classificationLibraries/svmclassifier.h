#ifndef SVMCLASSIFIER_H
#define SVMCLASSIFIER_H

#include "classificationLibraries/basicclassifier.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>

class SVMClassifier : public BasicClassifier{
private:
    CvSVM *svm;
    CvSVMParams *params;
    bool trained;
public:
    SVMClassifier(int kernel_type = CvSVM::RBF,int svm_type = CvSVM::C_SVC);
    ~SVMClassifier();

    bool train(std::vector<std::vector<double> > &train_samples, std::vector<double> &samples_labels);
    std::vector<double> classify(std::vector<std::vector<double> > &classify_samples);
    double classify(std::vector<double> &classify_sample);

    bool save(std::string filename);
    bool load(std::string filename);

};

#endif // SVMCLASSIFIER_H
