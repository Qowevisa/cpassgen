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
