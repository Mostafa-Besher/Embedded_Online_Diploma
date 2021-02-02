/*
 * Assignment1_6.c
 * program to Swap Two Numbers
 *
 *  Created on: Feb 1, 2021
 *      Author: mostafa
 */

#include <stdio.h>
void main()
{
	float a, b, hold;
	printf("Enter value of a : ");
	fflush(stdin); fflush(stdout);
	scanf("%f", &a);
	printf("\nEnter value of b : ");
	fflush(stdin); fflush(stdout);
	scanf("%f", &b);
	hold = a;
	a = b;
	b = hold;
	printf("\nAfter swapping, value of a = %f\n", a);
	printf("\nAfter swapping, value of b = %f\n", b);
}
