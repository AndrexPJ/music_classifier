#ifndef BASICCLASSIFIER_H
#define BASICCLASSIFIER_H

#include <vector>

class BasicClassifier
{
public:
    BasicClassifier();
    virtual ~BasicClassifier();
    virtual bool train(std::vector< std::vector<double> > &train_samples, std::vector<double> &samples_labels)  = 0;
    virtual std::vector<double> classify(std::vector< std::vector<double> > &classify_samples) = 0;
    virtual double classify(std::vector<double> &classify_sample) = 0;
};

#endif // BASICCLASSIFIER_H
