/*
 * program_to_take_anumber_and_sum_all_his_digits.c
 *
 *  Created on: Feb 22, 2021
 *      Author: mostafa
 */
#include <stdio.h>
#include <stdlib.h>
int sum_digits(void);

int main()
{
	printf("Sum = %d", sum_digits());
	return 0;
}

int sum_digits(void)
{
	int  sum = 0, n = 0;
	char c;
	printf("Enter integer : ");
	fflush(stdin);	fflush(stdout);

	do
	{
		scanf("%c", &c);
		n = atoi(&c);
		sum += n;
	}
	while(c != '\n');
	return sum;
}
