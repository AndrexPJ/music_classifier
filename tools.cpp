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


