#ifndef COUNCILCLASSIFIER_H
#define COUNCILCLASSIFIER_H

#include "classificationLibraries/basicclassifier.h"
#include "classificationLibraries/boostclassifier.h"
#include "classificationLibraries/svmclassifier.h"

class CommitteeClassifier : public BasicClassifier
{
private:
    std::vector<BasicClassifier*> expert_classifiers;
    BasicClassifier* master_classifier;

public:

    CommitteeClassifier(std::vector<BasicClassifier*> expert_classifiers);
    CommitteeClassifier(BasicClassifier* master_classifier,std::vector<BasicClassifier*> expert_classifiers);
    ~CommitteeClassifier();
    bool train(std::vector< std::vector<double> > &train_samples, std::vector<double> &samples_labels);
    bool train(AudioFeatureExcerpt &excerpt);

    double classify(std::vector<double> &classify_sample);
    double classifyPercent(std::vector<double> &classify_sample);
    std::vector<double> expertsInterview(std::vector<double> &classify_sample);

    bool save(std::string filename);
};


class CommitteeClassiferFactory
{
public:
    static CommitteeClassifier* getCommitteeClassifier(std::string genre, std::string master_classifiers_path = "./master_classifiers/" ,std::string expert_classifiers_path = "./expert_classifiers/");
};

#endif // COUNCILCLASSIFIER_H
