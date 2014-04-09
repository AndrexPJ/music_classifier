#ifndef BASICCLASSIFIER_H
#define BASICCLASSIFIER_H

#include <vector>
#include <math.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>

#include "basicClasses/audiofeatureexcerpt.h"

class BasicClassifier
{
protected:
    virtual cv::Mat vectorToMat(std::vector<double> &vector);
    virtual cv::Mat vectorToMat(std::vector< std::vector<double> > &vector);
public:
    BasicClassifier();
    virtual ~BasicClassifier();

    virtual bool train(AudioFeatureExcerpt &excerpt);
    virtual bool train(std::vector< std::vector<double> > &train_samples, std::vector<double> &samples_labels) = 0;

    virtual double test(AudioFeatureExcerpt &test_excerpt);

    virtual std::vector<double> classify(std::vector< std::vector<double> > &classify_samples) = 0;
    virtual double classify(std::vector<double> &classify_sample) = 0;

    virtual bool load(std::string filename) = 0;
    virtual bool save(std::string filename) = 0;
};

#endif // BASICCLASSIFIER_H
