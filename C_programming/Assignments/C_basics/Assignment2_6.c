/*
 * Assignment2_6.c
 *
 *  Created on: Feb 1, 2021
 *      Author: mostafa
 */

#include <stdio.h>

void main()
{
	int number, i,sum = 0;
	printf("Enter an integer : ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &number);
	for(i=0; i<=number; i++)
		sum += i;
	printf("sum = %d", sum);
}


