#include "wfft.h"

bool WFFT::perform(const std::vector<double> &Input,  std::vector< std::vector<complex> > &Output , WindowFunction &window,int window_size, int hop_size){
 int N  = Input.size();

 int prefix_size,suffix_size;
 prefix_size = suffix_size = 0;

 if(window_size == 0) return false;
 if(window_size & (window_size-1)) return false;


 //Output.resize((N/hop_size) * (window_size/2));
 int output_i = 0;

 complex *input_array = new complex[window_size];
 complex *temp_array = new complex[window_size];


 for(int i = 0; i + window_size < N; i += hop_size){
     for(int j = 0; j < window_size; j++){
         input_array[j] = Input[i+j] * window.perform(j,window_size);
     }

    CFFT::Forward(input_array,temp_array,window_size);
    Output[output_i].resize(window_size/2);

    for(int j = 0; j < window_size/2; j++){
         Output[output_i][j] = temp_array[j];
    }

    output_i++;

 }



 delete temp_array;
 delete input_array;
 return true;
}
