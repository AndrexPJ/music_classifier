#ifndef WINDOWFUNCTIONS_H
#define WINDOWFUNCTIONS_H

#include <math.h>
class WindowFunction
{
protected:
    double *values;
    int window_size;
public:
    WindowFunction();
    WindowFunction(int window_size);
    virtual double perform(int n);
};


class RectangleWindowFunction : public WindowFunction{
public:
    RectangleWindowFunction(int window_size);
};

class  HanningWindowFunction : public WindowFunction{

public:
    HanningWindowFunction(int window_size);
};

#endif // WINDOWFUNCTIONS_H
