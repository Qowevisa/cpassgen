#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../inc/cpassgen.h"
#include "../inc/bit.h"
#include "../inc/math.h"
#include "../inc/gnr.h"

void gen_part_1(unsigned char **gen) {
	unsigned int prime = 0;
	unsigned char *bits = NULL;
	gen_new_prime(&prime);
	// processing 256 prime numbers
	for (int i = 0; i < bb; i++) {
		int_to_bits(prime, &bits);
		for (int j = 0; j < 4; j++) {
			if (i + j < bb) {
				(*gen)[i + j] = (*gen)[i + j] ^ bits[j];
			}
		}
		free(bits);
		gen_new_prime(&prime);
	}
}

int main(int argc, char *argv[]) {
	unsigned char first_block[sq];
	memset(first_block, 0, sq);
	for (int i = 0; i < bs; i++) {
		for (int j = 0; j < 4; j++) {
			first_block[i*4 + j] = code[i];
            mvnbitr(&first_block[i*4 + j], j);
        }
    }
	// gen
	unsigned char *gen = (unsigned char*)calloc(bb, sizeof(unsigned char));
	// First shuffle
	gen_part_1(&gen);
	unsigned char left_block[mb];
	unsigned char right_block[mb];
	memset(left_block, ~0, mb);
	memset(right_block, 0, mb);
	return 0;
}
