/*
 * Assignment1_5.c
 * Program to Find ASCII Value of a Character
 *
 *  Created on: Feb 1, 2021
 *      Author: mostafa
 */

#include <stdio.h>

void main()
{
	char charater;
	printf("Enter a character : ");
	fflush(stdin);
	fflush(stdout);
	scanf("%c", &charater);
	printf("\nAscii value of %c = %d", charater, charater);
}


