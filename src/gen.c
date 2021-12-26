#include <stdlib.h>
#include <string.h>
#include "../inc/gen.h"
#include "../inc/math.h"
#include "../inc/bit.h"
#include "../inc/random.h"

#define bs 16
#define sq 64
#define mb 128
#define bb 256

void gen_init(u_char gen[]) {
    for (int cycle = 0; cycle < 5; cycle++) {
        for (int i = 0; i < bb; i++) {
            gen[i] = gen[i] ^ (gen_rand() % 256);
        }
    }
}

void gen_part_1(u_char gen[]) {
	u_int prime = 0;
	u_char *bits = NULL;
	gen_new_prime(&prime);
	// processing 256 prime numbers
	for (int i = 0; i < bb; i++) {
		int_to_bits(prime, &bits);
		for (int j = 0; j < 4; j++) {
			if (i + j < bb) {
				gen[i + j] = gen[i + j] ^ bits[j];
			}
		}
		free(bits);
		gen_new_prime(&prime);
	}
}

void gen_part_2(u_char gen[]) {
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
			gen[i] = gen[i] ^ expanded[i / 2];
		} else {
			gen[i] = gen[i] ^ ROTR(expanded[mb - (i / 2) - 1], 3);
		}
	}
}

void gen_new_seed(u_int *seed, u_char gen[], char *arg) {
    size_t len = strlen(arg);
    int i = 0;
    u_int tmp = 0;
    u_int sum = 0;
    u_int bit = 1 << 31;
    while (i != bb) {
        if ((gen[i] >> 7) & 1) {
            tmp |= bit;
        }
        bit >>= 1;
        if (bit == 0) {
            bit = 1 << 31;
            sum += tmp;
            tmp = 0;
        }
        i++;
    }
    for (size_t i = 0; i < len; i++) {
        sum += arg[i];
    }
    *seed = sum;
}

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

void rbcalc(u_char rblock[], char *arg) {
    size_t len = strlen(arg);
    size_t processed = 0;
    while (processed != len) {
        rblock[processed % mb] += arg[processed] + (gen_rand() % 256);
        processed++;
    }
    while (processed % mb != 0) {
        rblock[processed % mb] += gen_rand() % 256;
        processed++;
    }
    //
    u_int *ucast = (u_int*)rblock;
    for (u_int i = 0; i < mb/4; i++) {
        ucast[i] = ROTR_UINT(ucast[i], 17);
    }
}

void lbcalc(u_char lblock[], char *arg) {
    size_t len = strlen(arg);
    size_t processed = 0;
    while (processed != len) {
        lblock[processed % mb] = lblock[processed % mb] ^ (arg[processed] + (gen_rand() % 256));
        processed++;
    }
    while (processed % mb != 0) {
        lblock[processed % mb] = lblock[processed % mb] ^ (gen_rand() % 256);
        processed++;
    }
    //
    u_int *ucast = (u_int*)lblock;
    for (u_int i = 0; i < mb/4; i++) {
        ucast[i] = ROTL_UINT(ucast[i], 13);
    }
}

static const char ABC1[] = "ABCDEFGHIJKLM";
static const char ABC2[] = "NOPQRSTUVWXYZ";
static const char SPC[]  = "@:#LZdWsxZwcG";

static const char abc1[] = "abcdefghijklm";
static const char abc2[] = "nopqrstuvwxyz";
static const char num[]  = "1234567890521";

void get_passwd(u_char lb[], u_char rb[], char passwd[], const unsigned int len) {
    u_char c = 0;
    u_char *bytes = (u_char*)calloc(len, 1);
    for (u_int i = 0; i < len; i++) {
        switch (len) {
            case 256:
                if (i % 2 == 0) {
                    bytes[i] = lb[i / 2];
                } else {
                    bytes[i] = rb[i / 2];
                }
                break;
            case 128:
                bytes[i] = bytes[i] ^ (lb[i] + rb[i]);
                break;
            case 64:
                for (int si = 0; si < 2; si++) {
                    bytes[i] = bytes[i] ^ (lb[i*2 + si] + rb[i*2 + si]);
                }
                break;
            case 32:
                for (int si = 0; si < 4; si++) {
                    bytes[i] = bytes[i] ^ (lb[i*4 + si] + rb[i*4 + si]);
                }
                break;
            default:
                if (i < 128) {
                    bytes[i] = bytes[i] ^ (3*(lb[i] + rb[i]) + 15);
                } else {
                    bytes[i] = bytes[i] ^ (bytes[i - 1] + bytes[i - 65] + bytes[i - 128]);
                }
        }
        //
        c = bytes[i];
        u_char lead_bit = c & 0x80;
        u_char next_two_bits = c & 0x60;
        u_char last_five = c & 0x1F;
        if (lead_bit) { // shifted or special
            switch (next_two_bits % 3) {
                case 0:
                    passwd[i] = ABC1[last_five % (sizeof(ABC1) - 1)];
                    break;
                case 1:
                    passwd[i] = ABC2[last_five % (sizeof(ABC2) - 1)];
                    break;
                case 2:
                    passwd[i] = SPC[last_five % (sizeof(SPC) - 1)];
                    break;
            }
        } else { // notshifted or number
            switch (next_two_bits % 3) {
                case 0:
                    passwd[i] = abc1[last_five % (sizeof(abc1) - 1)];
                    break;
                case 1:
                    passwd[i] = abc2[last_five % (sizeof(abc2) - 1)];
                    break;
                case 2:
                    passwd[i] = num[last_five % (sizeof(num) - 1)];
                    break;
            }
        }
    }
    if (passwd[len - 1] == '@' ||
        passwd[len - 1] == ':' ||
        passwd[len - 1] == '#') {
        passwd[len - 1] = ABC2[bytes[16] % sizeof(ABC2)];
    }
    passwd[len] = '\0';
}

