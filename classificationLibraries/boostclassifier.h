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

    bool train(AudioFeatureExcerpt &excerpt);
    bool train(std::vector< std::vector<double> > &train_samples, std::vector<double> &samples_labels);

    std::vector<double> classify(std::vector< std::vector<double> > &classify_samples);
    double classify(std::vector<double> &classify_sample);

    bool load(std::string filename);
    bool save(std::string filename);

    BasicClassifier* clone();
};

#endif // BOOSTCLASSIFIER_H
