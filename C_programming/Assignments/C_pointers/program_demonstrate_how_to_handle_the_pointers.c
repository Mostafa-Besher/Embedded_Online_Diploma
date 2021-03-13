/*
 * program_demonstrate_how_to_handle_the_pointers.c
 *
 *  Created on: Mar 12, 2021
 *      Author: mostafa
 */

#include <stdio.h>

int main()
{
	int m = 29;
	printf("Address of m : %p\nValue of m : %d\n", &m, m);
	int *ab = &m;
	printf("Now ab is assigned with the address of m\n");
	printf("Address of pointer ab : %p\ncontent of pointer ab : %d\n", ab, *ab);
	m = 34;
	printf("Now the value of m is assigned to 34 m\n");
	printf("Address of pointer ab : %p\ncontent of pointer ab : %d\n", ab, *ab);
	*ab = 7;
	printf("The variable pointer ab is assigned with the value 7 now\n");
	printf("Address of m : %p\nValue of m : %d\n", &m, m);
	return 0;
}

