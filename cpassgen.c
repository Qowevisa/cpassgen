#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "config.h"

void mvnbitr(char *c, int n) {
	int counter = 0;
	if (n < 0)
		n = 0;
	else if (n >= 8) {
		(*c) = 255;
		return;
	}
	while (counter != n) {
		(*c) = ((*c) << 1) | 1;
		counter++;
	}
	return;
}

void mvnbitl(char *c, int n) {
	int counter = 0;
	if (n < 0)
		n = 0;
	else if (n >= 8) {
		(*c) = 255;
		return;
	}
	while (counter != n) {
		(*c) = ((*c) >> 1) | 128;
		counter++;
	}
	return;
}

void ROTR(unsigned char *c, int n) {
	if (n >= 8 || n <= 0) {
        n %= 8;
    }
	int counter = 0;
	unsigned char bits = 255;
	bits = bits >> (8 - n);
	unsigned char head = (*c & bits) << (8 - n);
	unsigned char rest = (*c >> n);
	(*c) = head | rest;
	return;
}

void ROTL(unsigned char *c, int n) {
	if (n >= 8 || n <= 0) {
        n %= 8;
    }
	int counter = 0;
	unsigned char bits = 255;
	bits = bits << (8 - n);
	unsigned char head = (*c & bits) >> (8 - n);
	unsigned char rest = (*c << n);
	(*c) = head | rest;
	return;
}

void X44(unsigned char *c, const unsigned char c1) {
	(*c) = ((*c) << 4) ^ (c1 >> 4);
}


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

int main(int argc, char *argv[]) {
	char first_block[sq];
	memset(first_block, 0, sq);
	for (int i = 0; i < bs; i++) {
		for (int j = 0; j < 4; j++) {
			first_block[i*4 + j] = code[i];
            mvnbitr(&first_block[i*4 + j], j);
        }
    }
	char left_block[mb];
	char right_block[mb];
	memset(left_block, ~0, mb);
	memset(right_block, 0, mb);
	return 0;
}
