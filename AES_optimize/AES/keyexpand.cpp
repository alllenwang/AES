#include <stdio.h>
#include <string.h>
#include "keyexpand.h"
#include "encrypt.h"
unsigned char key[44][4]={0x01,0x02,0x03,0x04,
							0x05,0x06,0x07,0x08,
							0x09,0x0a,0x0b,0x0c,
							0x0d,0x0e,0x0f,0x00};
unsigned char Rcon[10] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1b,0x36};
unsigned char mul[16][16][7] = {};

void T(unsigned char w[4],int i)
{
	unsigned char temp = w[0];
	w[0] = w[1];
	w[1] = w[2];
	w[2] = w[3];
	w[3] = temp;
	w[0] = change(w[0]);
	w[1] = change(w[1]);
	w[2] = change(w[2]);
	w[3] = change(w[3]);
	w[0] = w[0] ^ Rcon[i];
}
void expand_key()
{
	for (int i = 4; i < 44 ; i ++)
	{
		if(i % 4 != 0)
		{
			key[i][0] = key[i-4][0]	^ key[i-1][0];
			key[i][1] = key[i-4][1]	^ key[i-1][1];
			key[i][2] = key[i-4][2]	^ key[i-1][2];
			key[i][3] = key[i-4][3]	^ key[i-1][3];
		}
		else
		{
			unsigned char temp[4];
			for(int j = 0 ; j < 3 ; j ++)
			{
				temp[j] = key[i-1][j];
			}
			T(temp,i/4);
			key[i][0] = key[i-4][0]	^ temp[0];
			key[i][1] = key[i-4][1]	^ temp[1];
			key[i][2] = key[i-4][2]	^ temp[2];
			key[i][3] = key[i-4][3]	^ temp[3];
		}
	}
	
}
void calculate_mul()
{
	for(int i = 0 ; i < 16 ; i ++)
	{
		for(int j = 0 ; j < 16 ; j ++)
		{
			unsigned char temp = (i<<4) + j;
			mul[i][j][0] = mul_gf8(0x01,temp);
			mul[i][j][1] = mul_gf8(0x02,temp);
			mul[i][j][2] = mul_gf8(0x03,temp);
			mul[i][j][3] = mul_gf8(0x09,temp);
			mul[i][j][4] = mul_gf8(0x0b,temp);
			mul[i][j][5] = mul_gf8(0x0d,temp);
			mul[i][j][6] = mul_gf8(0x0e,temp); 
		}
	}
}