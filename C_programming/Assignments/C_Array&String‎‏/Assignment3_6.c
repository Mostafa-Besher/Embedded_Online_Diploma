/*
 * Assignment3_6.c
 * program to find character frequency in a string
 *
 *  Created on: Feb 8, 2021
 *      Author: mostafa
 */

#include <stdio.h>
#include <string.h>

int main()
{
	char string[40], c;
	int counter = 0, i;
	printf("Enter a string : ");
	fflush(stdin); fflush(stdout);
	gets(string);

	if(strlen(string) < 40)
	{
		printf("\nEnter a character to find frequency : ");
		fflush(stdin); fflush(stdout);
		scanf("%c", &c);

		for(i=0; i<strlen(string); i++)
		{
			if(string[i] == c)
			{
				counter++;
			}
		}

		if(counter != 0)
			printf("frequency of %c = %d", c, counter);
		else
			printf("character not found !");
	}

	else
		printf("Enter a shorter string ");
	return 0;
}
