/*
 * Assignment3_5.c
 * program to search an element in array
 *
 *  Created on: Feb 8, 2021
 *      Author: mostafa
 */

#include <stdio.h>

int main()
{
	int array[30], element, no_elements, i;
	printf("Enter no of elements : ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &no_elements);

	if(no_elements != 0 && no_elements <=30)
	{
		printf("\nEnter array elements : ");
		fflush(stdin); fflush(stdout);

		for(i=0; i<no_elements; i++)
		{
			scanf("%d", &array[i]);
		}

		printf("\nEnter an element to be searched : ");
		fflush(stdin); fflush(stdout);
		scanf("%d", &element);
		//search code
		for(i=0; i<no_elements; i++)
		{
			if(array[i]==element)
			{
				printf("Element found at location %d", i+1);
				break;
			}
		}

		if(i==no_elements)
			printf("Element not found !");
	}
	else
		printf("Enter number of elements between 1 and 30");
	return 0;
}
