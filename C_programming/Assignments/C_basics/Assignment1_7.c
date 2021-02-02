/*
 * Assignment1_7.c
 * program to swap two numbers without temp variable
 *
 *  Created on: Feb 1, 2021
 *      Author: mostafa
 */

#include <stdio.h>
void main()
{
	float a, b;
	printf("Enter value of a : ");
	fflush(stdin); fflush(stdout);
	scanf("%f", &a);
	printf("\nEnter value of b : ");
	fflush(stdin); fflush(stdout);
	scanf("%f", &b);
	a = a + b;
	b = a - b;
	a = a - b;
	printf("\nAfter swapping, value of a = %f\n", a);
	printf("\nAfter swapping, value of b = %f\n", b);
}


