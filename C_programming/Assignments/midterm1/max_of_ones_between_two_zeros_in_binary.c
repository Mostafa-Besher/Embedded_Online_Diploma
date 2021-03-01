/*
 * max_of_ones_between_two_zeros_in_binary.c
 *
 *  Created on: Feb 23, 2021
 *      Author: mostafa
 */

#include <stdio.h>
int max_ones_binary(int num);

int main()
{
	int number;
	printf("Enter number : ");
	fflush(stdin);	fflush(stdout);
	scanf("%d", &number);
	printf("Max ones between two zeros in binary =  %d", max_ones_binary(number));
	return 0;
}

int max_ones_binary(int num)
{
	int max = 0, counter0 = 0, counter1 = 0;
	unsigned int bin;

	while(num >= 0)
	{
		bin = num % 2;
		num = num / 2;

		if(bin == 0)
		{
			counter0++;
		}

		if(counter0 == 1 && bin == 1)
		{
			counter1++;
		}

		if(counter0 == 2 && counter1 == 0)
		{
			counter0 = 0;
		}

		if(num == 0)
		{
			num = -1;
			counter0++;
		}

		if(counter0 == 2 && counter1 >= 1)
		{
			if(counter1 > max)
				max = counter1;

			counter0 = 1;
			counter1 = 0;
		}
	}
	return max;
}
