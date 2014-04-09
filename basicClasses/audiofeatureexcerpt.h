#ifndef AUDIOFEATUREEXCERPT_H
#define AUDIOFEATUREEXCERPT_H

#include <vector>

class AudioFeatureExcerpt : public std::pair<std::vector<std::vector<double> >, std::vector<double> >
{
public:
    AudioFeatureExcerpt(std::vector<std::vector<double> > &feature_samples, std::vector<double> &labels);
    AudioFeatureExcerpt();
    std::vector<std::vector<double> > getFeatureSamples() const;
    std::vector<double> getLabels() const;

    int getSize() const;

};

#endif // AUDIOFEATUREEXCERPT_H
