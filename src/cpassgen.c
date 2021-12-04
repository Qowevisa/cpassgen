#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../inc/cpassgen.h"
#include "../inc/bit.h"
#include "../inc/math.h"

void gen_init(u_char **gen) {
    for (int cycle = 0; cycle < 5; cycle++) {
        for (int i = 0; i < bb; i++) {
            (*gen)[i] = (*gen)[i] ^ (rand() % 256);
        }
    }
}

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

#define LINES_N 33

// for now it's the only function
u_char tt(u_char c) {
    return
    ROTR(
        ROTR(
            ROTR(~c, 5),
            ROTL(~c, 3)),
        ROTL(
            ROTL(~c, 3),
            ROTR(~c, 5))
        );
}

void seed_from_block(u_int *seed, u_char block[]) {
    // TODO: get 8/16/32 different setups
    //  with different functions and then
    //  functional pointer comes handy
    u_char (*transform)(u_char) = &tt;
    u_char data[4] = { 89, 226, 199, 19 };
    u_int tmp = 0;
    u_char fbcast[sq];
    for (int i = 0; i < sq; i++) {
        fbcast[i] = block[i];
    }
    u_int *ufbcast = (u_int*)fbcast;
    for (int cycle = 0; cycle < 10; cycle++) {
        for (u_int i = 0; i < sq; i++) {
            fbcast[i] = ROTR(fbcast[i] + data[i % 4] - i*3, data[i % 4]);
        }
        //
        for (u_int i = 0; i < (u_int)sq/sizeof(u_int); i++) {
            tmp = tmp ^ ufbcast[i];
        }
        //
        for (u_int i = 0; i < 4; i++) {
            data[i] = (*transform)(data[i]);
        }
    }
    *seed = tmp;
}

int main() {
	u_char first_block[sq];
	memset(first_block, 0, sq);
	for (int i = 0; i < bs; i++) {
		for (int j = 0; j < 4; j++) {
            first_block[i*4 + j] = mvnbitr(code[i], j);
        }
    }
    // creating seed from first_block
    u_int seed = 0;
    seed_from_block(&seed, first_block);
    srand(seed);
	// gen
	u_char *gen = (u_char*)calloc(bb, sizeof(u_char));
    gen_init(&gen);
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
