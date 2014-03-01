#ifndef CORRELATIONFUNCTIONS_H
#define CORRELATIONFUNCTIONS_H


#include "fastFourierTransform/fft.h"
#include "tools.h"
#include <vector>
#include <math.h>

class CorrelationFunction{
protected:
    std::vector<double> values;
    int interval_size;
    virtual bool normalize();
public:
    CorrelationFunction();
    CorrelationFunction(std::vector<double> first_in_values, std::vector<double> second_in_values);

    virtual double perform(int n);
    virtual int getIntervalSize() const;

    virtual std::vector<double> getValues() const;

};

class AutocorrelationFunction : public CorrelationFunction{
public:
    AutocorrelationFunction(std::vector<double> in_values);
};


#endif // CORRELATIONFUNCTIONS_H
