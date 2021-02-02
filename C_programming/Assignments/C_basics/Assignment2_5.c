/*
 * Assignment2_5.c
 * program to check a character is alphabet or not
 *
 *  Created on: Feb 1, 2021
 *      Author: mostafa
 */

#include <stdio.h>

void main()
{
	char character;
	printf("Enter a character : ");
	fflush(stdin); fflush(stdout);
	scanf("%c", &character);
	character = (int)character;
	//comparing entered character with ASCII of alphabets(capital&small)
	if((character >= 65 && character <=90) || (character >= 97 && character <=122))
	{
		character = (char)character;
		printf("%c is an alphabet", character);
	}
	else
		printf("%c is not an alphabet", character);
}


