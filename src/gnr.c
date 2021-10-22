#include "../inc/gnr.h"

void X44(unsigned char *c, const unsigned char c1) {
	(*c) = ((*c) << 4) ^ (c1 >> 4);
}

