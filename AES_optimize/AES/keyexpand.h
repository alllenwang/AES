#ifndef __KEYEXPAND_H__
#define __KEYEXPAND_H__
#include <stdlib.h>
extern unsigned char key[44][4];
extern unsigned char mul[16][16][7];
extern unsigned char Rcon[10];
void calculate_mul();
void expand_key();
void T(unsigned char w[4],int i);

#endif