/*
 * Assignment3_4.c
 * program to insert an element in specified location in an array
 *
 *  Created on: Feb 8, 2021
 *      Author: mostafa
 */

#include <stdio.h>

int main()
{
	int array[30], no_elements, i, element, location;
	printf("Enter number of elements:  ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &no_elements);

	if(no_elements != 0 && no_elements < 30)
	{
		printf("Enter array elements : ");
		fflush(stdin); fflush(stdout);

		for(i=0; i<no_elements; i++)
		{
			scanf("%d", &array[i]);
		}

		printf("Enter element to be inserted: ");
		fflush(stdin); fflush(stdout);
		scanf("%d", &element);
		printf("Enter the location : ");
		fflush(stdin); fflush(stdout);
		scanf("%d", &location);
		//shifting elements of array additional location
		for(i=no_elements-1; i>=location-1; i--)
		{
			array[i+1] = array[i];
		}
		//insert element in entered location
		array[location-1] = element;

		//printing elements of array
		for(i=0; i<=no_elements;i++)
		{
			printf("%d\t", array[i]);
		}
	}
	else
		printf("Enter number of elements between 1 and 30");

	return 0;
}
