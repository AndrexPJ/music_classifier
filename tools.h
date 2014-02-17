#ifndef TOOLS_H
#define TOOLS_H
#include <vector>

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
    int size = in_vector.size();

    if(size == 0) return 0;

    T temp = in_vector[0];

    if(size == 1) return temp;


    for(int i = 1; i < size; i++)
        temp += in_vector[i];

    return temp/size;

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
    if (t >= T(0)) return T(1);
    return T(0);
}


#endif // TOOLS_H
