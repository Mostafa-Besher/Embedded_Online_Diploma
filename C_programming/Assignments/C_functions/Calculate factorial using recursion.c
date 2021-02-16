/*
 * Calculate factorial using recursion.c
 *
 *  Created on: Feb 15, 2021
 *      Author: mostafa
 */

#include <stdio.h>
int factorial(int number);

int main()
{
	int num;
	printf("Enter a positive integer: ");
	fflush(stdin);  fflush(stdout);
	scanf("%d", &num);
	if(num <= 0)
		printf("Enter positive integer!");
	else
		printf("Factorial of %d : %d", num, factorial(num));
	return 0;
}

int factorial(int number)
{
	if(number == 1)  // base case
		return 1;
	else
		return (number * factorial(number - 1));
}


