/*
 * Assignment3_2.c
 * program to calculate averge of number of elements stored in array
 *
 *  Created on: Feb 7, 2021
 *      Author: mostafa
 */

#include <stdio.h>

void main()
{
	float sum = 0.0, array[30];
	int n, i;
	printf("Enter the number of data : ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &n);

	if(n != 0 && n <= 30)
	{
		for(i=0; i<n; i++)
		{
			printf("Enter number : ");
			fflush(stdin); fflush(stdout);
			scanf("%f", &array[i]);
		}

		for(i=0; i<n; i++)
		{
			sum += array[i];
		}

		printf("Average = %f", sum/n);
	}

	else
		printf("Enter numbers less than 30 and greater than 0");

}
