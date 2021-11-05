#ifndef __cpassgen__math_h
#define __cpassgen__math_h
#include <math.h>

float Q_rsqrt(float number);
void gen_new_prime(unsigned int * prime);
unsigned int reverse_uint(unsigned int num);
unsigned int shuff_uint(unsigned int num);


typedef union {
	unsigned int num;
	unsigned char arr[4];
} uint_c;

#endif // __cpassgen__math_h
