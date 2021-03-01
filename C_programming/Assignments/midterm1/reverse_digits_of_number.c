/*
 * reverse_digits_of_number.c
 *
 *  Created on: Feb 23, 2021
 *      Author: mostafa
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void reverse_digits(void);

int main()
{
	reverse_digits();
	return 0;
}

void reverse_digits(void)
{
	int arr[15], i = 0;
	char c;
	printf("Enter integer : ");
	fflush(stdin);	fflush(stdout);

	while((c = getchar())!= '\n')
	{
		arr[i] = atoi(&c);
		i++;
	}

	i--;
	printf("Reversed number : ");
	for(; i>=0; i--)
	{
		printf("%d", arr[i]);
	}

}
