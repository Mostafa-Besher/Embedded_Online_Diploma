/*
 * count_ones_in_binary.c
 *
 *  Created on: Feb 22, 2021
 *      Author: mostafa
 */

#include <stdio.h>
int binary_count_ones(int num);


int main()
{
	int number;
	printf("Enter integer number : ");
	fflush(stdin);	fflush(stdout);
	scanf("%d", &number);
	printf("number of ones in %d =  %d", number, binary_count_ones(number));
	return 0;
}

int binary_count_ones(int num)
{
	unsigned int bin;
	int  counter = 0;

	while(num != 0)
	{
		bin = num % 2;
		num = num / 2;
		if(bin == 1)
			counter++;
	}
	return counter;
}
