/*
 * Reverse_sentence_using_recursion.c
 *
 *  Created on: Feb 15, 2021
 *      Author: mostafa
 */

#include <stdio.h>
#include <string.h>
void reverse_sentence(char string[]);
//static char reverse[30];

int main()
{
	char sentence[30];
	printf("Enter a sentence : ");
	fflush(stdin);	fflush(stdout);
	gets(sentence);
	printf("reversed sentence : ");
	reverse_sentence(sentence);
	return 0;
}

void reverse_sentence(char string[])
{
	if(string[0] == '\0')	//base case
	{
		return;
	}

	else
	{
		reverse_sentence(string + 1);  //string + 1 = &string[1]
		printf("%c", string[0]);
	}
}


