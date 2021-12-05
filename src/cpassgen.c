#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../inc/cpassgen.h"
#include "../inc/bit.h"
#include "../inc/math.h"
#include "../inc/gen.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        fprintf(stderr, "Usage: cpassgen <STRING>\n");
        return 1;
    }
	u_char first_block[sq] = {0};
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
    u_char gen[bb] = {0};
    gen_init(gen);
	// First shuffle
	gen_part_1(gen);
	// Second shuffle
	gen_part_2(gen);
    // Handling user input
    for (int i = 1; i < argc; i++) {
        // getting new_seed for every arg
        gen_new_seed(&seed, gen, argv[i]);
        srand(seed);
        //
        u_char left_block[mb] = {0};
        memset(left_block, ~0, mb);
        lbcalc(left_block, argv[i]);
        //
        u_char right_block[mb] = {0};
        memset(right_block, 0, mb);
        rbcalc(right_block, argv[i]);
        //
        printf("%s :: ", argv[i]);
        char password[33];
        get_passwd(left_block, right_block, password);
        printf("%s\n", password);
    }
	return 0;
}
