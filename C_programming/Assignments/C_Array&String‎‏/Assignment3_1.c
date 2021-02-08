/*
 * Assignment3_1.c
 *
 *  Created on: Feb 7, 2021
 *      Author: mostafa
 */

#include <stdio.h>

void main()
{
	float matrix1[2][2], matrix2[2][2], sum_matrix[2][2];
	int i, j;
	printf("Enter elements of 1st matrix : \n");

	for(i=0; i<2; i++)
	{
		for(j=0; j<2; j++)
		{
			printf("Enter element a%d%d: ", i, j);
			fflush(stdin); fflush(stdout);
			scanf("%f", &matrix1[i][j]);
		}
	}

	printf("Enter elements of 2nd matrix : \n");

	for(i=0; i<2; i++)
	{
		for(j=0; j<2; j++)
		{
			printf("Enter element b%d%d: ", i, j);
			fflush(stdin); fflush(stdout);
			scanf("%f", &matrix2[i][j]);
		}
	}
	// sum of two matrices
	printf("Sum matrix : \n");

	for(i=0; i<2; i++)
	{
		for(j=0; j<2; j++)
		{
			sum_matrix[i][j] = matrix1[i][j] + matrix2[i][j];
			printf("%f\t", sum_matrix[i][j]);
		}
		printf("\n");
	}

}
