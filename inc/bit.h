#ifndef __cpassgen__bit_h
#define __cpassgen__bit_h

unsigned char mvnbitr(unsigned char c, int n);
unsigned char mvnbitl(unsigned char c, int n);
unsigned char ROTR(unsigned char c, int n);
unsigned char ROTL(unsigned char c, int n);
unsigned int ROTR_UINT(unsigned int num, int n);
unsigned int ROTL_UINT(unsigned int num, int n);
unsigned char COMP(unsigned int num);
void int_to_bits(unsigned int num, unsigned char **out);
unsigned char get_byte(unsigned int num, unsigned int ind);


#endif // __cpassgen__bit_h
