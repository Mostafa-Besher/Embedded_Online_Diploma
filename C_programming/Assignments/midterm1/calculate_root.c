/*
 * calculate_root.c
 *
 *  Created on: Feb 22, 2021
 *      Author: mostafa
 */

#include <stdio.h>
#include <math.h>
double root_func(int num);

int main()
{
	int number;
	printf("Enter an integer : ");
	fflush(stdin);	fflush(stdout);
	scanf("%d", &number);
	printf("Root of %d = %.3lf", number, root_func(number));
	return 0;
}

double root_func(int num)
{
	double root;
	root = sqrt(num);
	return root;
}
