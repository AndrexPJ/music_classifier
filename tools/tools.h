#ifndef TOOLS_H
#define TOOLS_H

#include <vector>
#include <numeric>
#include <math.h>
#include <algorithm>
#include <functional>
#include <string>
#include <boost/filesystem.hpp>

namespace Tools {

unsigned int nearestPowerOfTwoAbove(unsigned int number);
std::vector<std::string> getAllFileNamesInDirectory(std::string dir_path, std::string extension);
std::vector<std::string> getRandomFileNames(std::string dir_path, int count, std::string extension);
std::pair<std::vector<std::string>, std::vector<std::string> > getTwoFileNamesHeaps(std::string dir_path, int first_count, int second_count,  std::string extension);

template <class T>
T getAverage(std::vector<T> &in_vector);

template <class T>
T getAverage(T a, T b);

template <class T>
std::vector<T> getAverage(std::vector<T> &a, std::vector<T> &b);

template <class T>
T signum(T t);

template <class T>
std::vector< std::vector<T> > getSimilarityMatrix(std::vector< std::vector<T> > &vectors);

template <class T>
T getGeneralizedMean(std::vector<T> &vector, double power);

template <class T>
T getCentroid(std::vector<T> &vector);

template <class T>
T getVariance(std::vector<T> &vector, T mean);


}


template <class T>
T Tools::getAverage(std::vector<T> &in_vector){
    if(in_vector.empty()) return 0;
    if(in_vector.size() == 1) return in_vector[0];
    return (std::accumulate(in_vector.begin(),in_vector.end(),T(0)) / in_vector.size());
}

template <class T>
T Tools::getAverage(T a, T b){
    return (a+b)/(T(2));
}


template <class T>
std::vector<T> Tools::getAverage(std::vector<T> &a, std::vector<T> &b){
    int size;

    if(a.size() > b.size()) size = b.size();
    else size = a.size();

    std::vector<T> result;
    result.resize(size);

    for(int i = 0; i < size; i++)
        result[i] = Tools::getAverage(a[i],b[i]);

    return result;
}

template <class T>
T Tools::signum(T t){
    if (t > T(0)) return T(1);
    if (t < T(0)) return T(-1);
    return T(0);
}

template <class T>
std::vector< std::vector<T> > Tools::getSimilarityMatrix(std::vector<std::vector<T> > &vectors){

 T epsilon = std::numeric_limits<T>::epsilon();
 int N = vectors.size();
 if(N == 0) return vectors;
 int n = vectors[0].size();

 std::vector< std::vector<T> > result;
 result.resize(N);
 T v1_n, v2_n, scalar;


 for(int i = N - 1; i >= 0; i--){
     result[i].assign(N,1.0);
     for(int j = 0; j <i; j++){
         v1_n = 0.0;
         v2_n = 0.0;
         scalar = 0.0;

         for(int k = 0; k < n; k++)
         {
             scalar += vectors[i][k] * vectors[j][k];
             v1_n += vectors[i][k] * vectors[i][k];
             v2_n += vectors[j][k] * vectors[j][k];
         }
         v1_n = sqrt(v1_n);
         v2_n = sqrt(v2_n);

         if((v1_n <= epsilon) && (v2_n <= epsilon))
             result[i][j] = 1.0;

         if((v1_n <= epsilon) || (v2_n <= epsilon))
             result[i][j] = 0.0;
         else
            result[i][j] = scalar / (v1_n * v2_n);
     }

     for(int j = i + 1; j < N; j++)
         result[i][j] = result[j][i];

 }
 return result;
}

template <class T>
T Tools::getGeneralizedMean(std::vector<T> &vector, double power){
    T mean = T(0);

    double norm = 1.0 / vector.size();

    for(int i = 0; i < vector.size(); i++)
        mean += pow(double(vector[i]), power);

    return pow((double(mean) * norm), 1.0 / power);
}


template <class T>
T Tools::getCentroid(std::vector<T> &vector){
    int size = vector.size();
    T weighted_sum = T(0);
    T sum = T(0);

    for(int i = 0; i < size; i++){
        weighted_sum += i * vector[i];
        sum += vector[i];
    }

    return (weighted_sum / (sum * size));
}

template <class T>
T Tools::getVariance(std::vector<T> &vector, T mean){
    T variance = T(0);
    T temp;
    int size = vector.size();

    for(int i = 0; i < size; i++){
        temp = vector[i] - mean;
        variance += temp * temp;
    }
    return variance / size;
}


#endif // TOOLS_H
