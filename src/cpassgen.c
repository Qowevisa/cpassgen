#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../inc/cpassgen.h"
#include "../inc/bit.h"
#include "../inc/math.h"

void gen_part_1(u_char **gen) {
	u_int prime = 0;
	u_char *bits = NULL;
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

void gen_part_2(u_char **gen) {
	u_int fib[32] = {0};
	fib[0] = 1;
	fib[1] = 1;
	// init fibonacci numbers
	for (int i = 2; i < 32; i++) {
		fib[i] = fib[i - 1] + fib[i - 2];
	}
	// just horizontal mirroring-ish
	for (int i = 0; i < 16; i++) {
		fib[i] += fib[31 - i];
		fib[i] >>= (i / 7) + 1;
	}
	// real shuffle
	for (int i = 0; i < 32; i++) {
		fib[i] |= reverse_uint(fib[i]);
		fib[i] = ROTR_UINT(shuff_uint(fib[i]), 13 + (i / 3));
	}
	u_char expanded[mb];
	for (int i = 0; i < mb; i++) {
		if (i % 2 == 0) {
			expanded[i] = get_byte(fib[i / 8], (i % 8) / 2);
		} else {
			expanded[i] = COMP(ROTL_UINT(fib[i / 8], (i % 8) / 2));
		}
	}
	for (int i = 0; i < bb; i++) {
		if (i % 2 == 0) {
			(*gen)[i] = (*gen)[i] ^ expanded[i / 2];
		} else {
			(*gen)[i] = (*gen)[i] ^ ROTR(expanded[mb - (i / 2) - 1], 3);
		}
	}
}

int main() {
	u_char first_block[sq];
	memset(first_block, 0, sq);
	for (int i = 0; i < bs; i++) {
		for (int j = 0; j < 4; j++) {
            first_block[i*4 + j] = mvnbitr(code[i], j);
        }
    }
	// gen
	u_char *gen = (u_char*)calloc(bb, sizeof(u_char));
	// First shuffle
	gen_part_1(&gen);
	// Second shuffle
	gen_part_2(&gen);
	u_char left_block[mb];
	u_char right_block[mb];
	memset(left_block, ~0, mb);
	memset(right_block, 0, mb);
	return 0;
}
