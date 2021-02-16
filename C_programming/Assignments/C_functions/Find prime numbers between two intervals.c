/*
 * Find prime numbers between two intervals.c
 *
 *  Created on: Feb 15, 2021
 *      Author: mostafa
 */

#include <stdio.h>
void prime_numbers(int num1, int num2);

int main()
{
	int number1, number2;
	printf("Enter two numbers : ");
	fflush(stdin);  fflush(stdout);
	scanf("%d %d", &number1, &number2);
	printf("prime numbers between %d and %d : ", number1, number2);
	prime_numbers(number1, number2);
	return 0;
}

void prime_numbers(int num1, int num2)
{
	int i, j;
	for(i = num1; i <= num2; i++)
	{
		if(i == 1)
			continue;

		else
		{
			for(j = 2; j <= 9; j++)
			{
				if(i == j)	//skip dividing number by itself
					continue;

				else
				{
					if(i % j == 0)
						break;
				}
			}
		}

		if((i % j) != 0)
			printf("%d ", i);
	}
}
