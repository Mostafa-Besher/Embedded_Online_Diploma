/*
 * Assignment 2_8.c
 * calculator program
 *
 *  Created on: Feb 1, 2021
 *      Author: mostafa
 */

#include <stdio.h>

void main()
{
	char operator;
	float num1, num2;
	printf("Enter operator either + or - or * or divide : ");
	fflush(stdin); fflush(stdout);
	scanf("%c", &operator);
	printf("\nEnter two operands : ");
	fflush(stdin); fflush(stdout);
	scanf("%f%f", &num1, &num2);

	switch(operator)
	{
	case '+' :
	{
		printf("\n%f + %f = %f", num1, num2, num1 + num2);

	}
	break;
	case '-' :
	{
		printf("\n%f - %f = %f", num1, num2, num1 - num2);

	}
	break;
	case '*' :
	{
		printf("\n%f * %f = %f", num1, num2, num1 * num2);

	}
	break;
	case '/' :
	{
		if(num2 == 0)
			printf("cannot be divide by zero! ");
		else
			printf("\n%f / %f = %f", num1, num2, num1 / num2);

	}
	break;
	}

}


