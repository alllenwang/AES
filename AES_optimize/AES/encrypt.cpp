#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encrypt.h"
#include "keyexpand.h"
unsigned char S[16][16]={0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5,
unsigned char change(unsigned char a)
{
	unsigned char b;
	b = S[a>>4][a % 16];
	return b;
}
void left_shift_one(unsigned char line[4])
{
	unsigned char temp = line[0];
	line[0] = line[1];
	line[1] = line[2];
	line[2] = line[3];
	line[3] = temp;
}
void line_shift(unsigned char state[4][4])
{
	for(int i = 1 ; i < 4 ; i ++)
	{
		for (int j = i ; j > 0 ; j --)
		{
			left_shift_one(state[i]);
		}
		
	}
}
void add_key(unsigned char state[4][4],unsigned char k[44][4],int count)
{
	for(int i = 0 ; i < 4 ; i ++)
	{
		for (int j = 0 ; j < 4 ; j ++)
		{
			state[j][i] = state[j][i] ^ k[i + count * 4][j];
		}
	}
}
unsigned char mul_gf8(unsigned char a, unsigned char b)
{
	int result = 0;
	int t = b;
//	printf("%d\n",t);
	while(a != 0)
	{
		if((a & 0x0001) == 1)
		{
			result = result ^ t; 
			t = t << 1;		
		}
		else
		{
			t = t << 1;
		}
		a = a >> 1;
	}
	unsigned char temp; 
	int m = 0x011b;
	while((result & 0xFF00) != 0)
	{
	
		int num = 0;
		int t = result;
		while(t >= 0x0100)
		{
			num ++;
			t = t >> 1;
		}
		num --;
		result = result ^ (m << num);
	}

	temp = result;
	return temp;
}
void row_mix(unsigned char state[4][4])
{
	unsigned char temp[4][4];
	for (int i = 0 ; i < 4 ; i ++)
	{
		for(int j = 0 ; j < 4 ; j ++)
		{
			temp[i][j] = state[i][j];
		}
	}
	for(int i = 0 ; i < 4 ; i ++)
	{
		state[0][i] = mul[temp[0][i]>>4][temp[0][i]%16][1] ^ mul[temp[1][i]>>4][temp[1][i]%16][2] ^ mul[temp[2][i]>>4][temp[2][i]%16][0] ^ mul[temp[3][i]>>4][temp[3][i]%16][0];
		state[1][i] = mul[temp[0][i]>>4][temp[0][i]%16][0] ^ mul[temp[1][i]>>4][temp[1][i]%16][1] ^ mul[temp[2][i]>>4][temp[2][i]%16][2] ^ mul[temp[3][i]>>4][temp[3][i]%16][0];
		state[2][i] = mul[temp[0][i]>>4][temp[0][i]%16][0] ^ mul[temp[1][i]>>4][temp[1][i]%16][0] ^ mul[temp[2][i]>>4][temp[2][i]%16][1] ^ mul[temp[3][i]>>4][temp[3][i]%16][2];
		state[3][i] = mul[temp[0][i]>>4][temp[0][i]%16][2] ^ mul[temp[1][i]>>4][temp[1][i]%16][0] ^ mul[temp[2][i]>>4][temp[2][i]%16][0] ^ mul[temp[3][i]>>4][temp[3][i]%16][1];	
	}
}
void line_row_operate(unsigned char state[4][4])
{
	unsigned char temp[4][4];
	for (int i = 0 ; i < 4 ; i ++)
	{
		for(int j = 0 ; j < 4 ; j ++)
		{
			temp[i][j] = state[i][j];
		}
	}
	for(int i = 0 ; i < 4 ; i ++)
	{
		state[0][i] = mul[temp[0][i]>>4][temp[0][i]%16][1] ^ mul[temp[1][(i+1)%4]>>4][temp[1][(i+1)%4]%16][2] ^ mul[temp[2][(i+2)%4]>>4][temp[2][(i+2)%4]%16][0] ^ mul[temp[3][(i+3)%4]>>4][temp[3][(i+3)%4]%16][0];
		state[1][i] = mul[temp[0][i]>>4][temp[0][i]%16][0] ^ mul[temp[1][(i+1)%4]>>4][temp[1][(i+1)%4]%16][1] ^ mul[temp[2][(i+2)%4]>>4][temp[2][(i+2)%4]%16][2] ^ mul[temp[3][(i+3)%4]>>4][temp[3][(i+3)%4]%16][0];
		state[2][i] = mul[temp[0][i]>>4][temp[0][i]%16][0] ^ mul[temp[1][(i+1)%4]>>4][temp[1][(i+1)%4]%16][0] ^ mul[temp[2][(i+2)%4]>>4][temp[2][(i+2)%4]%16][1] ^ mul[temp[3][(i+3)%4]>>4][temp[3][(i+3)%4]%16][2];
		state[3][i] = mul[temp[0][i]>>4][temp[0][i]%16][2] ^ mul[temp[1][(i+1)%4]>>4][temp[1][(i+1)%4]%16][0] ^ mul[temp[2][(i+2)%4]>>4][temp[2][(i+2)%4]%16][0] ^ mul[temp[3][(i+3)%4]>>4][temp[3][(i+3)%4]%16][1];	
	}
}
void encrypt_process(unsigned char state[4][4])
{
	add_key(state,key,0);
	for(int count = 1 ; count <10 ; count ++)
	{
		for (int i = 0 ; i < 4 ; i ++)
		{
			for(int j = 0 ; j < 4 ; j ++)
			{
				state[i][j] = change(state[i][j]);
			}
		}
		line_row_operate(state);
		add_key(state,key,count);
	}
	for (int i = 0 ; i < 4 ; i ++)
	{
		for(int j = 0 ; j < 4 ; j ++)
		{
			state[i][j] = change(state[i][j]);
		}
	}
	line_shift(state);
	add_key(state,key,10);
}