#ifndef TOOLS_H
#define TOOLS_H
#include <vector>

namespace Tools {

unsigned int nearestPowerOfTwoAbove(unsigned int number);


template <class T>
class SizingToPowerOfTwo{
public:
    static std::vector<T> perform(const std::vector<T> &in_vector, int &out_prefix_size, int &out_suffix_size);
};


}


template <class T>
std::vector<T> Tools::SizingToPowerOfTwo<T>::perform(const std::vector<T> &in_vector, int &out_prefix_size, int &out_suffix_size){
    int old_size = in_vector.size();

    if((old_size & (old_size - 1)) == 0){ // if old_size is power of two!
        out_prefix_size = 0;
        out_suffix_size = 0;
        return in_vector;
    }

    int new_size = Tools::nearestPowerOfTwoAbove(old_size);

    int prefix_size = (new_size - old_size)/2;
    int suffix_size = (new_size - old_size) - prefix_size;

    std::vector<T> temp;

    temp.resize(new_size);

    for(int i = 0; i < prefix_size; i++)
        temp.push_back(0);

        temp.insert(temp.end(),in_vector.begin(),in_vector.end());

    for(int i = 0; i < suffix_size; i++)
        temp.push_back(0);

    out_prefix_size = prefix_size;
    out_suffix_size = suffix_size;

    return temp;
}

#endif // TOOLS_H
