#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../inc/cpassgen.h"
#include "../inc/bit.h"
#include "../inc/math.h"
#include "../inc/gen.h"
#include "../inc/random.h"

enum states {
    silent = 1,
    only_first = 2,
    no_new_line = 4
};

void print_menu_help() {
    fprintf(stderr, 
        "Usage: cpassgen [OPTIONS] <STRING>\n"
        "Options:\n"
        "  -s   :  put just password for every usefull arg given\n"
        "  -f   :  parse only first usefull arg\n"
        "  -n   :  no new line symbol after every password\n");
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        print_menu_help();
        return 1;
    }
    if (strcmp(argv[1],"-h") == 0 ||
        strcmp(argv[1],"--help") == 0) {
        print_menu_help();
        return 1;
    }
    // parsing options
    u_char state = 0;
    u_int usefull_args = 0;
    for (int i = 1; i < argc; i++) {
        if (*argv[i] == '-') {
            for (size_t j = 1; j < strlen(argv[i]); j++) {
                switch (argv[i][j]) {
                    case 's':
                        state |= silent;
                        break;
                    case 'f':
                        state |= only_first;
                        break;
                    case 'n':
                        state |= no_new_line;
                        break;
                }
            }
        } else {
            usefull_args++;
        }
    }
    if (usefull_args == 0) {
        fprintf(stderr, "No useful args. Please provide at least one argument without dash \"-\" at the start. \n");
        print_menu_help();
        return 1;
    }
    //
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
    set_seed(seed);
	// gen
    u_char gen[bb] = {0};
    gen_init(gen);
	// First shuffle
	gen_part_1(gen);
	// Second shuffle
	gen_part_2(gen);
    // first_skip variable
    u_char fs = 0;
    // Handling user input
    for (int i = 1; i < argc; i++) {
        // skip args that starts with '-'
        if (*argv[i] == '-') {
            continue;
        } else {
            fs++;
        }
        // skip after first arg that don't start with '-'
        if (fs > 1 && state & only_first) {
            break;
        }
        // getting new_seed for every arg
        gen_new_seed(&seed, gen, argv[i]);
        set_seed(seed);
        //
        u_char left_block[mb] = {0};
        memset(left_block, ~0, mb);
        lbcalc(left_block, argv[i]);
        //
        u_char right_block[mb] = {0};
        memset(right_block, 0, mb);
        rbcalc(right_block, argv[i]);
        //
        if (!(state & silent)) {
            printf("%s :: ", argv[i]);
        }
        char password[33];
        get_passwd(left_block, right_block, password);
        printf("%s", password);
        if (!(state & no_new_line)) {
            printf("\n");
        }
    }
	return 0;
}
