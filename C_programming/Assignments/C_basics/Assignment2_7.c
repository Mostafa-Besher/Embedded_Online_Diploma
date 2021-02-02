/*
 * Assignment2_7.c
 * factorial program
 *
 *  Created on: Feb 1, 2021
 *      Author: mostafa
 */

#include <stdio.h>

void main()
{
	int number, fact = 1, i;
	printf("Enter an integer : ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &number);

	if(number >= 0)
	{
		for(i=number; i >=1; i--)
		{
			fact *= i;
		}
		printf("factorial = %d", fact);
	}
	else
		printf("Error!!! factorial of negative number does not exist");

}


