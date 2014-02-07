#include "windowfunctions.h"

WindowFunction::WindowFunction(){}


//### Window Functions list ###

RectangleWindowFunction::RectangleWindowFunction() : WindowFunction(){}
double RectangleWindowFunction::perform(int n, int N){
    if  ((n >= 0) && (n<N)) return 1.0;
    else                    return 0.0;
}


HannWindowFunction::HannWindowFunction() : WindowFunction(){}
double HannWindowFunction::perform(int n, int N){
    return 0.5 * (1 - cos((2*M_PI*n)/(N-1)));
}

//### ##################### ###
