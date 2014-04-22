#ifndef AUDIOFEATUREEXCERPT_H
#define AUDIOFEATUREEXCERPT_H

#include <vector>
#include <string>
class AudioFeatureExcerpt : public std::pair<std::vector<std::vector<double> >, std::vector<double> >
{
private:
    std::vector<std::string> class_names;
public:
    AudioFeatureExcerpt(std::vector<std::vector<double> > &feature_samples, std::vector<double> &labels);
    AudioFeatureExcerpt(std::vector<std::vector<double> > &feature_samples, std::vector<double> &labels, std::vector<std::string> &class_names);
    AudioFeatureExcerpt();
    std::vector<std::vector<double> > getFeatureSamples() const;
    std::vector<double> getLabels() const;
    std::vector<std::string> getClassNames() const;

    int getSize() const;

};

#endif // AUDIOFEATUREEXCERPT_H
