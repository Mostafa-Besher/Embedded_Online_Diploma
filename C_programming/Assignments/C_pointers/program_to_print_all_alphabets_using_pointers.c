/*
 * program_to_print_all_alphabets_using_pointers.c
 *
 *  Created on: Mar 12, 2021
 *      Author: mostafa
 */

#include <stdio.h>

int main()
{
	int i;
	char c;
	char *p = &c;
	printf("Alphabets are : \n");

	for(i = 0; i < 26; i++)
	{
		*p = 'A' + i;
		printf("%c ", *p);
	}

	//========================
	//another method
	/*
	char arr[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *p = arr;
	printf("Alphabets are : \n");
	do
	{
		printf("%c ", *p);
		p++;
	}
	while(*p != '\0');
	*/


	//========================
	//another method

	/*
	int i;
	char arr[27];
	char *p = arr;
	printf("Alphabets are : \n");

	for(i = 0; i < 26; i++)
	{
		*p = 'A' + i;
		p++;
	}

	p = arr;
	for(i = 0; i < 26; i++)
	{
		printf("%c ", *p);
		p++;
	}
	*/
	return 0;
}

