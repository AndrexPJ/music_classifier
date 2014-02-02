#ifndef WINDOWFUNCTIONS_H
#define WINDOWFUNCTIONS_H

#include <math.h>
class WindowFunction
{
public:
    WindowFunction();
    virtual double perform(int n,int N) = 0;
};


class RectangleWindowFunction : public WindowFunction{
public:
    RectangleWindowFunction();
    double perform(int n, int N);
};

class  HannWindowFunction : public WindowFunction{
public:
    HannWindowFunction();
    double perform(int n, int N);
};

#endif // WINDOWFUNCTIONS_H
