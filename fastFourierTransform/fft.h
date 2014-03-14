#ifndef _FFT_H_
#define _FFT_H_

//   Include complex numbers header
#include "complex.h"
#include "iostream"
#include <vector>
#include <fftw3.h>

class FFT{
public:
    static bool Forward(std::vector<complex> &Input, std::vector<complex> &Output, int N = -1);
    static bool Forward(std::vector<double> &Input, std::vector<complex> &Output);
    static bool Inverse(std::vector<complex> &Input, std::vector<complex> &Output, int N = -1);
    static bool Inverse(std::vector<double> &Input, std::vector<complex> &Output);

    static bool Forward2D(std::vector<std::vector<double> > &Input, std::vector<std::vector<complex> > &Output);
    static bool Forward2D(std::vector< std::vector<complex> > &Input,std::vector< std::vector<complex> > &Output);
    static bool Inverse2D(std::vector< std::vector<complex> > &Input,std::vector< std::vector<complex> > &Output);
    static bool Inverse2D(std::vector< std::vector<double> > &Input,std::vector< std::vector<complex> > &Output);
    static bool Perform2D(std::vector< std::vector<complex> > &Input,std::vector< std::vector<complex> > &Output, int sign);
    static bool Perform2D(std::vector< std::vector<double> > &Input,std::vector< std::vector<complex> > &Output, int sign);
};

class CFFT
{
public:
	//   FORWARD FOURIER TRANSFORM
	//     Input  - input data
	//     Output - transform result
	//     N      - length of both input data and result
	static bool Forward(const complex *const Input, complex *const Output, const unsigned int N);

	//   FORWARD FOURIER TRANSFORM, INPLACE VERSION
	//     Data - both input data and output
	//     N    - length of input data
	static bool Forward(complex *const Data, const unsigned int N);

	//   INVERSE FOURIER TRANSFORM
	//     Input  - input data
	//     Output - transform result
	//     N      - length of both input data and result
	//     Scale  - if to scale result
    static bool Inverse(const complex *const Input, complex *const Output, const unsigned int N, const bool Scale = false);

	//   INVERSE FOURIER TRANSFORM, INPLACE VERSION
	//     Data  - both input data and output
	//     N     - length of both input data and result
	//     Scale - if to scale result
    static bool Inverse(complex *const Data, const unsigned int N, const bool Scale = false);

protected:
	//   Rearrange function and its inplace version
	static void Rearrange(const complex *const Input, complex *const Output, const unsigned int N);
	static void Rearrange(complex *const Data, const unsigned int N);

	//   FFT implementation
	static void Perform(complex *const Data, const unsigned int N, const bool Inverse = false);

	//   Scaling of inverse FFT result
	static void Scale(complex *const Data, const unsigned int N);
};

#endif
