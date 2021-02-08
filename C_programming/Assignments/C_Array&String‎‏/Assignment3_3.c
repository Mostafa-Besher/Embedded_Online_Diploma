/*
 * Assignment3_3.c
 * program to find transpose of matrix
 *
 *  Created on: Feb 7, 2021
 *      Author: mostafa
 */

#include <stdio.h>

int main()
{
	float matrix[10][10], transpose[10][10];
	int i, j, n_row, n_column;
	printf("Enter rows and columns of matrix : \n");
	fflush(stdin);  fflush(stdout);
	scanf("%d%d", &n_row, &n_column);

	if((n_row != 0 && n_row <= 10) && (n_column != 0 && n_column <= 10))
	{

		for(i=0; i<n_row; i++)
		{
			for(j=0; j<n_column; j++)
			{
				printf("Enter element a%d%d : ", i, j);
				fflush(stdin);  fflush(stdout);
				scanf("%f", &matrix[i][j]);
			}
		}

		//printing entered matrix
		printf("Entered matrix : \n");

		for(i=0; i<n_row; i++)
		{
			for(j=0; j<n_column; j++)
			{
				printf("%f\t", matrix[i][j]);
			}
			printf("\n");
		}
		//calculating & printing entered matrix
		printf("Transpose of matrix : \n");

		for(i=0; i<n_column; i++)
		{
			for(j=0; j<n_row; j++)
			{
				transpose[i][j] = matrix[j][i];
				printf("%f\t", transpose[i][j]);
			}
			printf("\n");
		}

	}

	else
		printf("Enter rows & columns number between 1 and 10");

	/*
	for(i=0; i<n_row; i++)
	{
		for(j=0; j<n_column; j++)
		{
			printf("%f", transpose[i][j]);
		}
		printf("\n");
	}
	*/
	return 0;
}


