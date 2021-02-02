/*
 * Assignment2_4.c
 * program to check whether a number is positive or negative
 *
 *  Created on: Feb 1, 2021
 *      Author: mostafa
 */

#include <stdio.h>

void main()
{
	float number;
	printf("Enter a number : ");
	fflush(stdin); fflush(stdout);
	scanf("%f", &number);

	if(number > 0)
		printf("\nnumber is positive");
	else if (number < 0)
		printf("\nnumber is negative");
	else
		printf("\nnumber is zero");
}
