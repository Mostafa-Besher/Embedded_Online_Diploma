/*
 * Assignment2_3.c
 * program to find largest number among three numbers
 *
 *  Created on: Feb 1, 2021
 *      Author: mostafa
 */

#include <stdio.h>

void main()
{
	float num1, num2, num3;
	printf("Enter three numbers : ");
	fflush(stdin); fflush(stdout);
	scanf("%f %f %f", &num1, &num2, &num3);

	if(num1 > num2 && num1 > num3)
		printf("\nlargest number = %f", num1);

	else if(num2 > num1 && num2 > num3)
		printf("\nlargest number = %f", num2);

	else if(num3 > num1 && num3 > num2)
		printf("\nlargest number = %f", num3);
}
