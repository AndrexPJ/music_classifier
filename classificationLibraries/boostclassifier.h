#ifndef BOOSTCLASSIFIER_H
#define BOOSTCLASSIFIER_H

#include "classificationLibraries/basicclassifier.h"

class BoostClassifier : public BasicClassifier
{
private:
    CvBoost *boost;
public:
    BoostClassifier();
    ~BoostClassifier();

    virtual bool train(AudioFeatureExcerpt &excerpt);
    virtual bool train(std::vector< std::vector<double> > &train_samples, std::vector<double> &samples_labels);

    //virtual std::vector<double> classify(std::vector< std::vector<double> > &classify_samples);
    virtual double classify(std::vector<double> &classify_sample);

    virtual bool load(std::string filename);
    virtual bool save(std::string filename);
};

#endif // BOOSTCLASSIFIER_H
