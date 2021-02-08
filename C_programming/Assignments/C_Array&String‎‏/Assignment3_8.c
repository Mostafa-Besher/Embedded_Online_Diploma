/*
 * Assignment3_8.c
 * program to reverse a string
 *
 *  Created on: Feb 8, 2021
 *      Author: mostafa
 */

#include <stdio.h>
#include <string.h>

int main()
{
	char string[40], reverse_string[40];
	int i, j;
	printf("Enter a string : ");
	fflush(stdin); fflush(stdout);
	gets(string);

	if(strlen(string) < 40)
	{
		for(i=0, j=strlen(string)-1; i<strlen(string); i++, j--)
		{
			if(string[i] != '\0')
			{
				reverse_string[i] = string[j];
			}
			else
				break;
		}

		reverse_string[i] = '\0';	//end reverse_string with null
		printf("\nReverse string is : %s", reverse_string);
	}

	else
		printf("\nEnter shorter string ");
	return 0;
}
