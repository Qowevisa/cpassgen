#ifndef __cpassgen__gen_h
#define __cpassgen__gen_h

// WARNING: USES rand() !
void gen_init(unsigned char gen[]);
void gen_part_1(unsigned char gen[]);
void gen_part_2(unsigned char gen[]);
void gen_new_seed(unsigned int *seed, unsigned char gen[], char *arg);
void seed_from_block(unsigned int *seed, unsigned char block[]);
// WARNING: USES rand() !
void rbcalc(unsigned char rblock[], char *arg);
// WARNING: USES rand() !
void lbcalc(unsigned char lblock[], char *arg);
void get_passwd(unsigned char lb[], unsigned char rb[], char passwd[], const unsigned int len);

#endif // __cpassgen__gen_h

