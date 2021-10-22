#include "../inc/math.h"

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
