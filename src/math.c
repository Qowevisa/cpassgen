#include "../inc/math.h"
#include <stdbool.h>

float Q_rsqrt(float number) {
    long i;
    float x2, y;
    const float t = 1.5;

    x2 = number * 0.5;
    y = number;
    i = *(long*)&y;
    i = 0x5f3759df - (i >> 1);
    y = *(float*)&y;
    y = y*(t - (x2 * y * y));
    y = y*(t - (x2 * y * y));
    return y;
}

bool is_prime(unsigned int num) {
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

void gen_new_prime(unsigned int *prime) {
    (*prime)++;
    while (!is_prime(*prime)) {
        (*prime)++;
    }
}
