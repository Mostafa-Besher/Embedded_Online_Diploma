/*
 * Assignment2_2.c
 * program to check vowel or consonant
 *
 *  Created on: Feb 1, 2021
 *      Author: mostafa
 */

#include <stdio.h>

void main()
{
	char alphabet;
	printf("Enter an alphabet : ");
	fflush(stdin); fflush(stdout);
	scanf("%c", &alphabet);
	switch(alphabet)
	{
	case 'a' :
	case 'A' :
	case 'e' :
	case 'E' :
	case 'i' :
	case 'I' :
	case 'o' :
	case 'O' :
	case 'u' :
	case 'U' :
	{
		printf("\n%c is vowel", alphabet);
	}
	break;

	default:
		printf("\n%c is consonant", alphabet);
	break;

	}

}

