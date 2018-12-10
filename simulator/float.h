#ifndef FLOAT_H
#define FLOAT_H

// a op b
float fadd(float a, float b);
float fsub(float a, float b);
float fmul(float a, float b);
float finv(float f);
float fdiv(float a, float b);
float fsqrt(float f);

int feq(float a, float b);
int flt(float a, float b);
int fle(float a, float b);

float fneg(float f);
float itof(int i);
int ftoi(float f);


#endif
