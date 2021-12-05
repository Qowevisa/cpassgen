#include <stdbool.h>
#include <stdlib.h>
#include "../inc/math.h"
#include "../inc/bit.h"

float Q_rsqrt(float number) {
    long i;
    float x2, y;
    const float t = 1.5;

    x2 = number * 0.5;
    y = number;
    i = * (long*)&y;
    i = 0x5f3759df - (i >> 1);
    y = * (float*)&i;
    y = y*( t - (x2 * y * y));
    y = y*( t - (x2 * y * y));
    return y;
}


bool is_prime(u_int num) {
    if (num < 2) {
        return false;
    }
    switch (num) {
        case 2:
            return true;
            break;
        case 5:
            return true;
            break;
    }
    if (num % 2 == 0) {
        return false;
    } else if (num % 5 == 0) {
        return false;
    }
    for (int del = 3, counter = 3;
        del < sqrt(num);
        del += 2, counter++) {
        if (counter == 4) {
            del += 2;
            counter = 0;
        }
        if (num % del == 0) {
            return false;
        }
    }
    return true;
}

void gen_new_prime(u_int *prime) {
    (*prime)++;
    while (!is_prime(*prime)) {
        (*prime)++;
    }
}

u_int reverse_uint(u_int num) {
	u_int new_bit = 1 << 31;
	u_int bit = 1;
	u_int ret = 0;
	while (new_bit > 0) {
		if (num & bit) {
			ret |= new_bit;
		}
		new_bit >>= 1;
		bit <<= 1;
	}
	return ret;
}

u_int shuff_uint(u_int num) {
	uint_c tmp;
	uint_c ret;
	ret.num = 0;
	tmp.num = num;
	for (int i = 0; i < 4; i++) {
		int prev = i - 1;
		int next = i + 1;
		if (prev < 0) {
			prev += 4;
		} else if (next > 3) {
			next -= 4;
		}
		ret.arr[i] = ROTR(tmp.arr[prev] ^ tmp.arr[next], i*3);
	}
	return ret.num;
}
