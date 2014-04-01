#ifndef NOVELTYFUNCTIONS_H
#define NOVELTYFUNCTIONS_H

#include "basicClasses/audioampspectrum.h"
#include "basicClasses/audiospectrum.h"
#include <math.h>
#include <vector>
#include <limits>

class NoveltyFunction {
protected:
    std::vector < std::vector<double> > values;
    int interval_size, channels_count;

public:
    NoveltyFunction();
    NoveltyFunction(int interval_size, int channels_count);
    virtual double perform(int n, int channel);
    virtual std::vector< std::vector<double> > getValues() const;

    int getChannelsCount() const;
    int getIntervalSize() const;

};

class FluxNoveltyFunction : public NoveltyFunction{
protected:
    AudioSpectrum<double> spectrum;
public:
    FluxNoveltyFunction(AudioSpectrum<double> &spectrum);
};

class DuxburyNoveltyFunction : public NoveltyFunction{
protected:
    AudioSpectrum<complex> spectrum;
public:
    DuxburyNoveltyFunction(AudioSpectrum<complex> &specrtum);
};

class HainsworthNoveltyFunction : public NoveltyFunction{
protected:
    AudioSpectrum<double> spectrum;
public:
    HainsworthNoveltyFunction(AudioSpectrum<double> &spectrum);
};

#endif // NOVELTYFUNCTIONS_H
