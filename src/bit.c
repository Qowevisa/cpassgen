#include "../inc/bit.h"
#include "../inc/math.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

unsigned char mvnbitr(unsigned char c, int n) {
	int counter = 0;
	if (n < 0) {
		n = 0;
	} else if (n >= 8) {
		return 255;
	}
	while (counter != n) {
		c = (c << 1) | 1;
		counter++;
	}
	return c;
}

unsigned char mvnbitl(unsigned char c, int n) {
	int counter = 0;
	if (n < 0) {
		n = 0;
	} else if (n >= 8) {
		return 255;
	}
	while (counter != n) {
		c = (c >> 1) | 128;
		counter++;
	}
	return c;
}

unsigned char ROTR(unsigned char c, int n) {
	if (n >= 8 || n <= 0) {
        n %= 8;
    }
	unsigned char bits = 0xFF >> (8 - n);
	unsigned char head = (c & bits) << (8 - n);
	unsigned char rest = (c >> n); 
	return head | rest;
}

unsigned char ROTL(unsigned char c, int n) {
	if (n >= 8 || n <= 0) {
        n %= 8;
    }
	unsigned char bits = 0xFF << (8 - n);
	unsigned char head = (c & bits) >> (8 - n);
	unsigned char rest = (c << n);
	return head | rest;
}

void pul(unsigned int num) {
	unsigned int bit = 1 << 31;
	unsigned char counter = 0;
	for (int i = 0; i < 32; i++) {
		if (num & bit) {
			fputc('1', stdout);
		} else {
			fputc('0', stdout);
		}
		bit >>= 1;
		counter++;
		if (counter == 8) {
			counter = 0;
			fputc(' ', stdout);
		}
	}
	fputc('\n', stdout);
}

unsigned int ROTL_UINT(unsigned int num, int n) {
	if (n >= 32 || n <= 0) {
        n %= 32;
    }
	unsigned int bits = 0xFFFFFFFF << (32 - n);
	unsigned int head = (num & bits) >> (32 - n);
	unsigned int rest = (num << n);
	return head | rest;
}

unsigned int ROTR_UINT(unsigned int num, int n) {
	if (n >= 32 || n <= 0) {
        n %= 32;
    }
	unsigned int bits = 0xFFFFFFFF >> (32 - n);
	unsigned int head = (num & bits) << (32 - n);
	unsigned int rest = (num >> n);
	return head | rest;
}

unsigned char COMP(unsigned int num) {
	uint_c tmp;
	memset(tmp.arr, 0xC0, 4);
	tmp.num = num & tmp.num;
	unsigned char ret = 0;
	for (int i = 0; i < 4; i++) {
		ret |= (tmp.num >> (6 + i*8)) << i*2;
	}
	return ret;
}

// Uses Q_rsqrt and out will be char[4];
void int_to_bits(unsigned int num, unsigned char **out) {
	(*out) = (unsigned char*)malloc(4);
	unsigned char tmp_byte;
	unsigned char bit;
	float prm_f = Q_rsqrt(num);
	for (int i = 0; i < 4; i++) {
        tmp_byte = 0;
        bit = 128;
        while (bit > 0) {
            prm_f = prm_f * 2;
            unsigned int rest = (unsigned int)prm_f;
            prm_f -= rest;
            if (rest == 1) {
                tmp_byte += bit;
                bit /= 2;
            } else {
                bit /= 2;
            }
        }
        (*out)[i] = tmp_byte;
	}
}

unsigned char get_byte(unsigned int num, unsigned int ind) {
	if (ind > 3) {
		ind %= 4;
	}
	unsigned char tmp[4] = {0};
	unsigned int bit = 1 << 31;
	for (int i = 0; i < 32; i++) {
		if (num & bit) {
			tmp[i / 8] |= bit >> (3 - i/8)*8;
			bit >>= 1;
		} else {
			bit >>= 1;
		}
	}
	return tmp[ind];
}