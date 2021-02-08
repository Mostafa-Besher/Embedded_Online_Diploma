/*
 * Assignment3_7.c
 * program to find the length of a string
 *
 *  Created on: Feb 8, 2021
 *      Author: mostafa
 */

#include <stdio.h>
#include <string.h>

int main()
{
	char string[40];
	int length = 0, i;
	printf("Enter a string : ");
	fflush(stdin); fflush(stdout);
	gets(string);

	for(i=0; i<40; i++)
	{
		if(string[i] != '\0')
		{
			length++;
		}
		else
			break;
	}

	printf("\nLength of string : %d", length);
	return 0;
}
