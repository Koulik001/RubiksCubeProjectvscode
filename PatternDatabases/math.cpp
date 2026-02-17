#include "math.h"

uint32_t factorial(uint32_t n){
    return (n == 0)? 1: n * factorial(n - 1);
}

uint32_t nCk(uint32_t n, uint32_t k){
    if(k == 0 || k == n) return 1;
    else if(k == 1 || k == n - 1) return n;
    return (factorial(n)/factorial(k))/factorial(n - k);
}