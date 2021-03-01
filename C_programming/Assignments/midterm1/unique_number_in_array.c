/*
 * unique_number_in_array.c
 *
 *  Created on: Feb 23, 2021
 *      Author: mostafa
 */

#include <stdio.h>
int unique_no_array(unsigned int arr[], int size);

int main()
{
	unsigned int array[3] = {4,2,4};
	if(unique_no_array(array, 7) != -1)
		printf("Unique number in array =  %d", unique_no_array(array, 3));
	else
		printf("No unique element");

	return 0;
}

int unique_no_array(unsigned int arr[], int size)
{
	int i, j, key = -1;
	for(i=0; i<size; i++)
	{
		for(j=0; j<size;j++)
		{
			if(i == j)
	        {
				continue;
	        }

	        else
	        {
	        	if(arr[i] != arr[j] && j == size - 1)
	            {
	        		key = arr[i];
					//return key;
	            }

	            if(arr[i] == arr[j])
	            {
	            	break;
	            }
	        }

		}

	}

	if(i == size && key == 0)
	{
		return 0;
	}

	else
	{
		return key;
	}

}
