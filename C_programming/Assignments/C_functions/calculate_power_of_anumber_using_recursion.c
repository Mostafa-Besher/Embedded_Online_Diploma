/*
 * calculate_power_of_anumber_using_recursion.c
 *
 *  Created on: Feb 16, 2021
 *      Author: mostafa
 */

#include <stdio.h>
int power_func(int number, int power);

int main()
{
	int basenumber, power;
	printf("Enter base number : ");
	fflush(stdin);	fflush(stdout);
	scanf("%d",&basenumber);
	printf("Enter power number : ");
	fflush(stdin);	fflush(stdout);
	scanf("%d",&power);
	printf("%d ^ %d = %d", basenumber, power, power_func(basenumber, power));
	return 0;
}

int power_func(int number, int power)
{
	int p = 0;
	if(p == power)	//base case
	{
		return 1;
	}

	else
	{
		return number * power_func(number, power - 1);
	}
}

