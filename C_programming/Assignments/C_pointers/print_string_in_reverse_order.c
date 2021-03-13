/*
 * print_string_in_reverse_order.c
 *
 *  Created on: Mar 12, 2021
 *      Author: mostafa
 */
#include <stdio.h>
#include <string.h>

void reverse_string(char *ptr);

int main()
{
	char str[40];
	printf("Input a string : ");
	fflush(stdin);	fflush(stdout);
	gets(str);
	reverse_string(str);
	return 0;
}

void reverse_string(char strr[])
{

	printf("Reverse of the string : ");
	char *ptr = &strr[strlen(strr) - 1];

	while(ptr != strr)
	{
		printf("%c", *ptr);
		ptr--;

		if(ptr == strr)
			printf("%c", *ptr);
	}


	//==========================
	//another method without using (strlen) function
	/*
	 	printf("Reverse of the string : ");
		char *ptr = strr;
		while(*ptr != '\0')
		{
			ptr++;
		}

		ptr--;	//to make ptr points to last character before '\0'
		while(ptr != strr)
		{
			printf("%c", *ptr);
			ptr--;

			if(ptr == strr)
				printf("%c", *ptr);
		}
	*/
}

