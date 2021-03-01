/*
 * sum_of_numbers_from_1_to_100_without_loops.c
 *
 *  Created on: Feb 23, 2021
 *      Author: mostafa
 */

#include <stdio.h>
int sum_without_loops(void);

int main()
{
	printf("Sum of numbers from 1 to 100 : %d", sum_without_loops());
	return 0;
}

int sum_without_loops(void)
{
	static int sum = 0, i = 1;
	if(i <= 100)
	{
		sum +=i;
		i++;
		sum_without_loops();
	}
	return sum;
}

