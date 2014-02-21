#ifndef TOOLS_H
#define TOOLS_H
#include <vector>
#include <numeric>
namespace Tools {

unsigned int nearestPowerOfTwoAbove(unsigned int number);

template <class T>
T getAverage(std::vector<T> &in_vector);

template <class T>
T getAverage(T a, T b);

template <class T>
std::vector<T> getAverage(std::vector<T> &a, std::vector<T> &b);

template <class T>
T signum(T t);

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


#endif // TOOLS_H
