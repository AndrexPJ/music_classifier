#include "wfft.h"

bool WFFT::perform(const std::vector<double> &Input,  std::vector< std::vector<complex> > &Output , WindowFunction &window,int window_size, int hop_size){
 int N  = Input.size();

 int prefix_size,suffix_size;
 prefix_size = suffix_size = 0;

 if(window_size == 0) return false;
 if(window_size & (window_size-1)) return false;


 int output_i = 0;

 complex *input_array = new complex[window_size];
 complex *temp_array = new complex[window_size];


 for(int i = 0; i < N - window_size + 1; i += hop_size, output_i++){
     for(int j = 0; j < window_size; j++){
         input_array[j] = Input[i+j] * window.perform(j);
     }

    CFFT::Forward(input_array,temp_array,window_size);

    for(int j = 0; j < window_size/2; j++){
         Output[output_i][j] = temp_array[j]/sqrt(window_size);
    }
 }

 delete[] temp_array;
 delete[] input_array;
 return true;
}
