#include "tools.h"

int Tools::nearestPowerOfTwoAbove(int number){
    if(number <= 1) return 1;
    int power = 1;

    while(power < number){
        power <<= 1;
    }

    return power;
}
