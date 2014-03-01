#include "windowfunctions.h"

WindowFunction::~WindowFunction(){
    delete this->values;
}

WindowFunction::WindowFunction(){

}

WindowFunction::WindowFunction(int window_size){
    this->values = new double[window_size];
    this->window_size = window_size;
}

int WindowFunction::getWindowSize(){
    return this->window_size;
}


double WindowFunction::perform(int n){
    if((n < 0) || (n >= window_size)) return 0.0;
    return this->values[n];
}

//### Window Functions list ###

RectangleWindowFunction::RectangleWindowFunction(int window_size) : WindowFunction(window_size){
    for(int i = 0; i < window_size; i++)
        this->values[i] = 1.0;

}



HanningWindowFunction::HanningWindowFunction(int window_size) : WindowFunction(window_size){
    for(int i = 0; i < window_size; i++){
        this->values[i] =  0.5 * (1 - cos((2*M_PI*i)/(window_size-1)));
    }
}

//### ##################### ###
