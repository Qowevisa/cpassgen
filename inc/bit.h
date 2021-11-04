#ifndef __cpassgen__bit_h
#define __cpassgen__bit_h

void mvnbitr(unsigned char *, int);
void mvnbitl(unsigned char *, int);
void ROTR(unsigned char *, int);
void ROTL(unsigned char *, int);
void int_to_bits(unsigned int num, unsigned char **out);

#endif // __cpassgen__bit_h
