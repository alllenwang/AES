#include <iostream>
#include <time.h>
#include "decrypt.h"
#include "encrypt.h"
#include "keyexpand.h"
/*after optimize*/
int main()
{
	clock_t start, finish; 
	double Total_time; 
	calculate_mul();
	unsigned char data[16] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,
		0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};
	unsigned char state[4][4];
	for (int i = 0 ; i < 4 ; i ++)
	{
		for(int j = 0 ; j < 4 ; j ++)
		{
			state[i][j] = data[i + j * 4];
		}
	}
	for(int i = 0 ; i < 4 ; i ++)
	{
		for (int j = 0 ; j < 4 ; j ++)
		{
			printf("%x ",state[i][j]);
		}
		printf("\n");
	}
	start = clock(); 
	for(int i = 0 ; i < 1000 ; i ++)
	{
		encrypt_process(state);
		decrypt_process(state);
	}
	finish = clock(); 
	for(int i = 0 ; i < 4 ; i ++)
	{
		for (int j = 0 ; j < 4 ; j ++)
		{
			printf("%x ",state[i][j]);
		}
		printf("\n");
	}


	Total_time = (double)(finish-start); 
    printf( "%f ms\n", Total_time); 
}