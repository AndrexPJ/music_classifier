#ifndef AUDIORHYTHMDESCRIPTORS_H
#define AUDIORHYTHMDESCRIPTORS_H
#include "audioDescriptors/audiodescriptorextractor.h"
#include "audioDescriptors/noveltyfunctions.h"
#include "fastFourierTransform/fft.h"
#include <vector>
#include <tools.h>


class CorrelationFunction{
protected:
    std::vector<double> values;
    int interval_size;

public:
    CorrelationFunction();
    CorrelationFunction(std::vector<double> first_in_values, std::vector<double> second_in_values);

    double perform(int n);
    int getIntervalSize() const;

    std::vector<double> getValues() const;

};

class AutocorrelationFunction : public CorrelationFunction{
public:
    AutocorrelationFunction(std::vector<double> in_values);
};


class BeatHistogramDescriptorExtractor : public AudioDescriptorExtractor{
private:
    std::vector<double> histogram;
    int histogram_size;
public:
    BeatHistogramDescriptorExtractor(CorrelationFunction &c_func);
    std::vector<double> extract();

};




#endif // AUDIORHYTHMDESCRIPTORS_H
