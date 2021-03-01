/*
 * reverse_array_elements.c
 *
 *  Created on: Feb 23, 2021
 *      Author: mostafa
 */

#include <stdio.h>
void reverse(int array[], int size);

int main()
{
    int arr[20];
    reverse(arr, 5);
    return 0;
}

void reverse(int array[], int size)
{
    int i, j, reverse_arr[20];
    printf("Enter array elements : ");
    fflush(stdin);	fflush(stdout);

    for(i = 0; i <size; i++)
    {
        scanf("%d", &array[i]);
    }
    fflush(stdin);	fflush(stdout);
    printf("Reverse array :  ");

    for(i = size - 1, j = 0; i >= 0; i--, j++)
    {
        reverse_arr[j] = array[i];
        printf("%d ", reverse_arr[j]);
    }
}
