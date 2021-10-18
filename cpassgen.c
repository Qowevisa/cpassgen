#include <stdio.h>
#include <unistd.h>
#include <string.h>
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

void ROTR(char *c, int n) {
	if (n >= 8 || n <= 0)
		return;
	int counter = 0;
	char bits = 255;
	bits = bits >> (8 - n);
	char head = (*c & bits) << (8 - n);
	char rest = (*c >> n);
	(*c) = head | rest;
	return;
}

void X44(char *c, const char c1) {
	(*c) = ((*c) << 4) ^ (c1 >> 4);
}

int main(int argc, char *argv[]) {
	char first_block[sq];
	memset(first_block, 0, sq);
	for (int i = 0; i < bs; i++)
		for (int j = 0; j < 4; j++)
			first_block[i*4 + j] = mvnbitr(&code[i], j);
	char left_block[mb];
	char right_block[mb];
	memset(left_block, ~0, mb);
	memset(right_block, 0, mb);
	return 0;
}
