#ifndef AUDIORHYTHMDESCRIPTORS_H
#define AUDIORHYTHMDESCRIPTORS_H
#include "audioDescriptors/noveltyfunctions.h"
#include <fastFourierTransform/fft.h>
#include <vector>
#include <tools.h>
class AutocorrelationFunction{
protected:
    std::vector<double> values;
    int interval_size;

public:
    AutocorrelationFunction(std::vector<double> in_values);

    double perform(int n);
    int getIntervalSize() const;

    std::vector<double> getValues() const;
};


#endif // AUDIORHYTHMDESCRIPTORS_H
