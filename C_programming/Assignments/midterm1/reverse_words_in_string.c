/*
 * reverse_words_in_string.c
 *
 *  Created on: Feb 23, 2021
 *      Author: mostafa
 */

#include <stdio.h>
#include <string.h>
void reverse_words(char string[]);

int main()
{
	char string[30];
	printf("Enter a string : ");
	fflush(stdin);	fflush(stdout);
	gets(string);
	reverse_words(string);
	return 0;
}

void reverse_words(char string[])
{
	char str1[30], str2[30];
	int i = 0, j = 0;

	while(string[i] != ' ')
	{
		str1[i] = string[i];
		i++;
	}
	str1[i] = '\0';

	for(++i; string[i] != '\0'; i++, j++)
	{
		str2[j] = string[i];
	}
	str2[j] = '\0';

	strcat(str2, " ");
	printf("\nReversed array words : %s", strcat(str2, str1));

}
