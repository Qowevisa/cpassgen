#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "../inc/cpassgen.h"
#include "../inc/bit.h"
#include "../inc/math.h"
#include "../inc/gnr.h"


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
