/*
 * print_elements_of_array_in_reverse_order.c
 *
 *  Created on: Mar 12, 2021
 *      Author: mostafa
 */
#include <stdio.h>

void Reverse_array(int arr[]);
int size;

int main()
{
	int arr[15], i;
	printf("Input the number of elements to store in the array (max 15) : ");
	fflush(stdin);	fflush(stdout);
	scanf("%d", &size);
	printf("Input %d elements in the array : \n", size);

	for(i=0; i<size; i++)
	{
		printf("Element - %d : ", i+1);
		fflush(stdin);	fflush(stdout);
		scanf("%d", &arr[i]);
	}

	Reverse_array(arr);
	return 0;
}

void Reverse_array(int arr[])
{
	int *p_rev = &arr[size - 1];
	int i;
	printf("\nThe elements of array in reverse order are : \n");

	i = size;
	while(p_rev != arr)
	{
		printf("Element - %d : %d\n", i, *p_rev);
		p_rev--;
		i--;

		if(p_rev == arr)
			printf("Element - %d : %d", i, *p_rev);
	}
}
