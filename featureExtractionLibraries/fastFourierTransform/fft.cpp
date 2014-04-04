//   fft.cpp - impelementation of class
//   of fast Fourier transform - FFT
//
//   The code is property of LIBROW
//   You can use it on your own
//   When utilizing credit LIBROW site

//   Include declaration file
#include "fft.h"
//   Include math library
#include <math.h>


bool FFT::Forward(std::vector<complex> &Input, std::vector<complex> &Output, int N){
    if(N == -1){
    N = Input.size();
    if (N < 1 || N & (N - 1))
        return false;
    }
    Output.resize(N);

    complex *output = new complex[N];

    if(CFFT::Forward(Input.data(), output,N)){
    for(int i = 0; i < N; i++)
        Output[i] = output[i] / sqrt(N);

    delete[] output;
    return true;
    }

    delete[] output;
    return false;
}

bool FFT::Inverse(std::vector<complex> &Input, std::vector<complex> &Output, int N){
    if(N == -1){
    N = Input.size();
    if (N < 1 || N & (N - 1))
        return false;
    }
    Output.resize(N);

    complex *output = new complex[N];

    if(CFFT::Inverse(Input.data(), output,N)){
    for(int i = 0; i < N; i++)
        Output[i] = output[i] / sqrt(N);

    delete[] output;
    return true;
    }

    delete[] output;
    return false;
}

bool FFT::Forward(std::vector<double> &Input, std::vector<complex> &Output){
    int N = Input.size();
    if (N < 1 || N & (N - 1))
        return false;

    std::vector<complex> temp_input;
    temp_input.resize(N);
    for(int i = 0; i < N; i++)
        temp_input[i] = Input[i];

    return FFT::Forward(temp_input,Output,N);
}

bool FFT::Inverse(std::vector<double> &Input, std::vector<complex> &Output){
    int N = Input.size();
    if (N < 1 || N & (N - 1))
        return false;

    std::vector<complex> temp_input;
    temp_input.resize(N);
    for(int i = 0; i < N; i++)
        temp_input[i] = Input[i];

    return FFT::Inverse(temp_input,Output,N);

}

bool FFT::Forward2D(std::vector<std::vector<double> > &Input, std::vector<std::vector<complex> > &Output){
    return FFT::Perform2D(Input,Output,FFTW_FORWARD);
}

bool FFT::Inverse2D(std::vector<std::vector<double> > &Input, std::vector<std::vector<complex> > &Output){
    return FFT::Perform2D(Input,Output,FFTW_BACKWARD);
}

bool FFT::Perform2D(std::vector<std::vector<double> > &Input, std::vector<std::vector<complex> > &Output,int sign){
    int N = Input.size();
    if(N <= 0) return false;
    int M = Input[0].size();

    std::vector< std::vector<complex> > Input_c;
    Input_c.resize(N);

    for(int i = 0; i < N; i++){
        Input_c[i].resize(M);
        for(int j = 0; j < M; j++)
            Input_c[i][j] = Input[i][j];
    }

    return FFT::Perform2D(Input_c,Output,sign);
}

bool FFT::Forward2D(std::vector<std::vector<complex> > &Input, std::vector<std::vector<complex> > &Output){
    return FFT::Perform2D(Input,Output,FFTW_FORWARD);
}

bool FFT::Inverse2D(std::vector<std::vector<complex> > &Input, std::vector<std::vector<complex> > &Output){
    return FFT::Perform2D(Input,Output,FFTW_BACKWARD);
}

bool FFT::Perform2D(std::vector<std::vector<complex> > &Input, std::vector<std::vector<complex> > &Output, int sign){
    int N = Input.size();
    if(N <= 0) return false;
    int M = Input[0].size();



    fftw_complex *in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*N*M);
    fftw_complex *out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*N*M);

    fftw_plan plan;
    plan = fftw_plan_dft_2d(N,M,in,out, sign,FFTW_MEASURE);

    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            in[i * M + j][1] = Input[i][j].im();
            in[i * M + j][0] = Input[i][j].re();
        }
    }


    fftw_execute(plan);

    Output.resize(N);
    for(int i = 0; i < N; i++){
        Output[i].resize(M);
        for(int j = 0; j < M; j++){
            Output[i][j] = complex(out[i * M + j][0],out[i * M + j][1]) / sqrt(N*M);
        }
    }


    fftw_free(in);
    fftw_free(out);
    fftw_destroy_plan(plan);
    return true;
}

//   FORWARD FOURIER TRANSFORM
//     Input  - input data
//     Output - transform result
//     N      - length of both input data and result
bool CFFT::Forward(const complex *const Input, complex *const Output, const unsigned int N)
{
	//   Check input parameters
	if (!Input || !Output || N < 1 || N & (N - 1))
		return false;
	//   Initialize data
	Rearrange(Input, Output, N);
	//   Call FFT implementation
	Perform(Output, N);
	//   Succeeded
	return true;
}

//   FORWARD FOURIER TRANSFORM, INPLACE VERSION
//     Data - both input data and output
//     N    - length of input data
bool CFFT::Forward(complex *const Data, const unsigned int N)
{
	//   Check input parameters
	if (!Data || N < 1 || N & (N - 1))
		return false;
	//   Rearrange
	Rearrange(Data, N);
	//   Call FFT implementation
	Perform(Data, N);
	//   Succeeded
	return true;
}

//   INVERSE FOURIER TRANSFORM
//     Input  - input data
//     Output - transform result
//     N      - length of both input data and result
//     Scale  - if to scale result
bool CFFT::Inverse(const complex *const Input, complex *const Output, const unsigned int N, const bool Scale /* = true */)
{
	//   Check input parameters
	if (!Input || !Output || N < 1 || N & (N - 1))
		return false;
	//   Initialize data
	Rearrange(Input, Output, N);
	//   Call FFT implementation
	Perform(Output, N, true);
	//   Scale if necessary
	if (Scale)
		CFFT::Scale(Output, N);
	//   Succeeded
	return true;
}

//   INVERSE FOURIER TRANSFORM, INPLACE VERSION
//     Data  - both input data and output
//     N     - length of both input data and result
//     Scale - if to scale result
bool CFFT::Inverse(complex *const Data, const unsigned int N, const bool Scale /* = true */)
{
	//   Check input parameters
	if (!Data || N < 1 || N & (N - 1))
		return false;
	//   Rearrange
	Rearrange(Data, N);
	//   Call FFT implementation
	Perform(Data, N, true);
	//   Scale if necessary
	if (Scale)
		CFFT::Scale(Data, N);
	//   Succeeded
	return true;
}

//   Rearrange function
void CFFT::Rearrange(const complex *const Input, complex *const Output, const unsigned int N)
{
	//   Data entry position
	unsigned int Target = 0;
	//   Process all positions of input signal
	for (unsigned int Position = 0; Position < N; ++Position)
	{
		//  Set data entry
		Output[Target] = Input[Position];
		//   Bit mask
		unsigned int Mask = N;
		//   While bit is set
		while (Target & (Mask >>= 1))
			//   Drop bit
			Target &= ~Mask;
		//   The current bit is 0 - set it
		Target |= Mask;
	}
}

//   Inplace version of rearrange function
void CFFT::Rearrange(complex *const Data, const unsigned int N)
{
	//   Swap position
	unsigned int Target = 0;
	//   Process all positions of input signal
	for (unsigned int Position = 0; Position < N; ++Position)
	{
		//   Only for not yet swapped entries
		if (Target > Position)
		{
			//   Swap entries
			const complex Temp(Data[Target]);
			Data[Target] = Data[Position];
			Data[Position] = Temp;
		}
		//   Bit mask
		unsigned int Mask = N;
		//   While bit is set
		while (Target & (Mask >>= 1))
			//   Drop bit
			Target &= ~Mask;
		//   The current bit is 0 - set it
		Target |= Mask;
	}
}

//   FFT implementation
void CFFT::Perform(complex *const Data, const unsigned int N, const bool Inverse /* = false */)
{
	const double pi = Inverse ? 3.14159265358979323846 : -3.14159265358979323846;
	//   Iteration through dyads, quadruples, octads and so on...
	for (unsigned int Step = 1; Step < N; Step <<= 1)
	{
		//   Jump to the next entry of the same transform factor
		const unsigned int Jump = Step << 1;
		//   Angle increment
		const double delta = pi / double(Step);
		//   Auxiliary sin(delta / 2)
		const double Sine = sin(delta * .5);
		//   Multiplier for trigonometric recurrence
		const complex Multiplier(-2. * Sine * Sine, sin(delta));
		//   Start value for transform factor, fi = 0
		complex Factor(1.);
		//   Iteration through groups of different transform factor
		for (unsigned int Group = 0; Group < Step; ++Group)
		{
			//   Iteration within group 
			for (unsigned int Pair = Group; Pair < N; Pair += Jump)
			{
				//   Match position
				const unsigned int Match = Pair + Step;
				//   Second term of two-point transform
				const complex Product(Factor * Data[Match]);
				//   Transform for fi + pi
				Data[Match] = Data[Pair] - Product;
				//   Transform for fi
				Data[Pair] += Product;
			}
			//   Successive transform factor via trigonometric recurrence
			Factor = Multiplier * Factor + Factor;
		}
	}
}

//   Scaling of inverse FFT result
void CFFT::Scale(complex *const Data, const unsigned int N)
{
    const double Factor = 1. / double(N);
	//   Scale all data entries
	for (unsigned int Position = 0; Position < N; ++Position)
		Data[Position] *= Factor;
}
