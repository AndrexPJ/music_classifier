#include "tools.h"

unsigned int Tools::nearestPowerOfTwoAbove(unsigned int number){
    if(number <= 1) return 1;
    --number;
    number |= (number >> 1);
    number |= (number >> 2);
    number |= (number >> 4);
    number |= (number >> 8);
    number |= (number >> 16);
    return number + 1;
}

/*std::vector<double> Tools::experiment(std::vector<double> &func,std::vector<std::vector<double> > &basis){
    int N = basis.size();
    int n;
    int func_size = func.size();

    std::vector<double> result(N,0.0);

    for(int i = 0; i < N; i++){
        n = basis[i].size();
        for(int j = 0; j < func_size; j++)
            //result[i] += func[j] * basis[i][j%n];
            result[i] += (func[j] - basis[i][j%n]) * (func[j] - basis[i][j%n]);
        result[i] = sqrt(result[i]);
    }

    double norm = 0.0;
    for(int i = 0; i < N; i++)
        norm += result[i] * result[i];

    norm = sqrt(norm);
    for(int i = 0; i < N; i++)
        result[i] = result[i] /norm;

    return result;
}


double Tools::getScalar(std::vector<double> &first, std::vector<double> &second){
    return std::inner_product(first.begin(),first.end(),second.begin(),0.0);
}

std::vector<double> Tools::mulVector(std::vector<double> &vector, double num){
    std::vector<double> temp(vector.size());
    std::transform(vector.begin(),vector.end(),temp.begin(),std::bind1st(std::multiplies<double>(),num));
    return temp;
}

std::vector<double> Tools::sumVectors(std::vector<double> &first, std::vector<double> &second){
    int N = first.size();
    if(N != second.size()) return first;

    std::vector<double> result(N);

    for(int i = 0; i < N; i++)
        result[i] = first[i] + second[i];

    return result;
}

std::vector< std::vector<double> > Tools::getBasis(std::vector<std::vector<double> > &vectors, int vector_size){
    std::vector< std::vector<double> > result;
    int N = vectors.size();
    result.resize(N);

    for(int i = 0; i < N; i++)
        result[i].insert(result[i].begin(),vectors[i].begin(),vectors[i].begin() + vector_size);

    std::vector< std::vector<double> > temp = result;
    std::vector<double> temp_v;
    std::vector<double> temp_v2;
    double scalar_a, scalar_b;

    for(int i = 1; i < N; i++){
        temp_v.assign(temp[i].size(),0.0);
        for(int j = 0; j < i; j++){
            scalar_a = Tools::getScalar(temp[i],temp[j]);
            scalar_b = Tools::getScalar(temp[j],temp[j]);
            temp_v2 = Tools::mulVector(temp[j],scalar_a / scalar_b);
            temp_v = Tools::sumVectors(temp_v,temp_v2);
        }
        temp_v2 = Tools::mulVector(temp_v, -1);
        result[i] = Tools::sumVectors(result[i], temp_v2);
    }

    for(int i = 0; i < N; i++){
        scalar_a = Tools::getScalar(result[i],result[i]);
        scalar_a = 1/sqrt(scalar_a);

        result[i] = Tools::mulVector(result[i],scalar_a);
    }

    return result;

}

std::vector< std::vector<double> > Tools::experiment_w(std::vector<double> &func, std::vector<std::vector<double> > &basis, WindowFunction &window){
    int func_size = func.size();
    int N = func_size / window.getWindowSize();

    std::vector<std::vector<double> > result(N);
    std::vector<double> temp(window.getWindowSize());

    for(int i = 0; i < N; i++){
        for(int j = 0; j < window.getWindowSize(); j++)
            temp[j] = func[i+j] * window.perform(j);

        result[i] = Tools::experiment(temp,basis);
    }

    return result;
}
*/
