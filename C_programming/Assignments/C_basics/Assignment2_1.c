/*
 * Assignment2_1.c
 * program to check whether a number is even or odd
 *
 *  Created on: Feb 1, 2021
 *      Author: mostafa
 */

#include <stdio.h>
void main()
{
	int number;
	printf("Enter an integer you want to check : ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &number);

	if(number % 2 == 0)
		printf("\n%d is even", number);
	else
		printf("\n%d is odd", number);
}

