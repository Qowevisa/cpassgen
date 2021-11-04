#include "../inc/bit.h"

void mvnbitr(unsigned char *c, int n) {
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

void mvnbitl(unsigned char *c, int n) {
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


// out will be char[4];
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