#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "../inc/cpassgen.h"
#include "../inc/bit.h"
#include "../inc/math.h"
#include "../inc/gnr.h"

// out will be char[4];
void prime_to_bits(unsigned int prime, unsigned char **out) {
	(*out) = (unsigned char*)malloc(4);
	unsigned char tmp_byte;
	unsigned char bit;
	float prm_f = Q_rsqrt(prime);
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
