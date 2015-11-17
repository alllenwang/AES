#ifndef __DECRYPT_H__
#define __DECRYPT_H__
#include <stdlib.h>
extern unsigned char inverse_S[16][16];
unsigned char inverse_change(unsigned char a);
void right_shift_one(unsigned char line[4]);
void inverse_line_shift(unsigned char state[4][4]);
void inverse_row_mix(unsigned char state[4][4]);
void decrypt_process(unsigned char state[4][4]);
#endif