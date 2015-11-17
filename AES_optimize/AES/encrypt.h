#ifndef __ENCRYPT_H__
#define __ENCRYPT_H__
#include <stdlib.h>

extern unsigned char S[16][16]; 
unsigned char change(unsigned char a);
void line_shift(unsigned char state[4][4]);
void left_shift_one(unsigned char line[4]);
void add_key(unsigned char state[4][4],unsigned char k[44][4],int count);
unsigned char mul_gf8(unsigned char a, unsigned char b);
void row_mix(unsigned char state[4][4]);
void line_row_operate(unsigned char state[4][4]);
void encrypt_process(unsigned char state[4][4]);
#endif