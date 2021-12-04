#include "../inc/bit.h"
#include "../inc/math.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

u_char mvnbitr(u_char c, u_char n) {
	u_char counter = 0;
	if (n >= 8) {
		return 255;
	}
	while (counter != n) {
		c = (c << 1) | 1;
		counter++;
	}
	return c;
}

u_char mvnbitl(u_char c, u_char n) {
    u_char counter = 0;
	if (n >= 8) {
		return 255;
	}
	while (counter != n) {
		c = (c >> 1) | 128;
		counter++;
	}
	return c;
}

u_char ROTR(u_char c, u_char n) {
	if (n >= 8) {
        n %= 8;
    }
	u_char bits = 0xFF >> (8 - n);
	u_char head = (c & bits) << (8 - n);
	u_char rest = (c >> n); 
	return head | rest;
}

u_char ROTL(u_char c, u_char n) {
	if (n >= 8) {
        n %= 8;
    }
	u_char bits = 0xFF << (8 - n);
	u_char head = (c & bits) >> (8 - n);
	u_char rest = (c << n);
	return head | rest;
}

u_int ROTL_UINT(u_int num, u_int n) {
	if (n >= 32 || n <= 0) {
        n %= 32;
    }
	u_int bits = 0xFFFFFFFF << (32 - n);
	u_int head = (num & bits) >> (32 - n);
	u_int rest = (num << n);
	return head | rest;
}

u_int ROTR_UINT(u_int num, u_int n) {
	if (n >= 32 || n <= 0) {
        n %= 32;
    }
	u_int bits = 0xFFFFFFFF >> (32 - n);
	u_int head = (num & bits) << (32 - n);
	u_int rest = (num >> n);
	return head | rest;
}

u_char COMP(u_int num) {
	uint_c tmp;
	memset(tmp.arr, 0xC0, 4);
	tmp.num = num & tmp.num;
	u_char ret = 0;
	for (int i = 0; i < 4; i++) {
		ret |= (tmp.num >> (6 + i*8)) << i*2;
	}
	return ret;
}

// Uses Q_rsqrt and out will be char[4];
void int_to_bits(u_int num, u_char **out) {
	(*out) = (u_char*)malloc(4);
	u_char tmp_byte;
	u_char bit;
	float prm_f = Q_rsqrt(num);
	for (int i = 0; i < 4; i++) {
        tmp_byte = 0;
        bit = 128;
        while (bit > 0) {
            prm_f = prm_f * 2;
            u_int rest = (u_int)prm_f;
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

u_char get_byte(u_int num, u_int ind) {
	if (ind > 3) {
		ind %= 4;
	}
	u_char tmp[4] = {0};
	u_int bit = 1 << 31;
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
