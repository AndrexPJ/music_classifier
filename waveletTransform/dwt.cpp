#include "dwt.h"

bool DWT::Forward(std::vector<double> Input, std::vector<double> &Output){
 int N = Input.size();
 int suffix_size = 0;

 if(N & (N-1)){
     N = Tools::nearestPowerOfTwoAbove(N);
     suffix_size = N  - Input.size();
     for(int i = 0; i < suffix_size; i++)
         Input.push_back(0);
 }

 double *data = new double[N];

 gsl_wavelet *wavelet;
 gsl_wavelet_workspace *workspace;

 wavelet = gsl_wavelet_alloc(gsl_wavelet_daubechies,4);
 workspace = gsl_wavelet_workspace_alloc(N);

 std::copy(Input.begin(),Input.end(),data);

 gsl_wavelet_transform_forward(wavelet,data,1,N,workspace);

 Output.insert(Output.end(),data,data+(N));

 gsl_wavelet_free(wavelet);
 gsl_wavelet_workspace_free(workspace);

 delete data;
 return true;
}
