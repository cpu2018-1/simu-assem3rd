#include <math.h>
#include "float.h"

//必要に応じて実装を変更してください

float fadd(float a, float b){

    return a + b;

}

float fsub(float a, float b){

    return a - b;
  
}

float fmul(float a, float b){

    return a * b;

}

float finv(float f){

    return 1 / f;

}

float fsqrt(float f){

    return sqrt(f);

}

float fneg(float f){

    return -f;

}

int feq(float a, float b){

    return ( a == b ? 1 : 0);

}

int flt(float a, float b){

    return ( a < b ? 1 : 0);

}

int fle(float a, float b){

    return ( a <= b ? 1 : 0);

}

float itof(int i){

    return (float) i;

}

int ftoi(float f){

    return (int) f;

}
