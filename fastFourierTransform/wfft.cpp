#include "wfft.h"

bool WFFT::perform(const std::vector<double> &Input, std::vector<complex> &Output, WindowFunction &window,int window_size, int offset){
 int N  = Input.size();

 if(window_size == 0) return false;
 if(N & (N-1)) return false;


 Output.resize(N);

 complex *input_array = new complex[N];
 complex *temp_array = new complex[window_size];

 for(int i = 0; i < N; i++)
     input_array[i] = Input[i] * window.perform(i % window_size,window_size);


 for(int i = 0; i < N; i += window_size){
    CFFT::Forward(input_array + i,temp_array,window_size);
    for(int j = 0; j < window_size; j++)
        Output[i+j] = temp_array[j]/window_size;
 }


 delete temp_array;
 delete input_array;
 return true;
}
