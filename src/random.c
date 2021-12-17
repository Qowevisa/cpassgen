#include <stdlib.h>
#include <limits.h>
#include "../inc/random.h"

typedef unsigned long long ull;
#define len sizeof(ull)

ull ROTR_ULL(ull num, ull n) {
    n %= len;
    ull bits = ULLONG_MAX >> n;
    ull head = (num & bits) << (8*len - n);
    ull tail = num >> n;
    return head | tail;
}

ull ROTL_ULL(ull num, ull n) {
    n %= len;
    ull bits = ULLONG_MAX << n;
    ull head = (num & bits) >> (8*len - n);
    ull tail = num << n;
    return head | tail;
}

ull __seed = 0;

ull ALPHA(ull num) {
    return (ROTR_ULL(num, 13) ^ ROTL_ULL(num, 7)) + num;
}

ull BETA(ull num) {
    u_char tmp =
        (num & 0x000000FF) ^
        (num & 0x0000FF00) ^
        (num & 0x00FF0000) ^
        (num & 0xFF000000) ;
    ull itmp = 
        0           |
        tmp << 0    |
        tmp << 8    |
        tmp << 16   |
        tmp << 24   ;
    return itmp;
}

void iterate_seed() {
    __seed = ALPHA(__seed) + ALPHA(BETA(__seed));
}

// interface

void set_seed(ull seed) {
    __seed = seed;
}

unsigned long long gen_rand() {
    iterate_seed();
    return __seed;
}
