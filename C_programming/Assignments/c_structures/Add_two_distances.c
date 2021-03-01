/*
 * Add_two_distances.c
 *
 *  Created on: Feb 28, 2021
 *      Author: mostafa
 */

#include <stdio.h>
void Enter_info(void);
void calculate_sum(void);

struct SDistance
{
	int feet;
	float inch;
};

struct SDistance gfirst, gsecond, gsum;

int main()
{
	Enter_info();
	calculate_sum();
	return 0;
}

void Enter_info(void)
{
	printf("Enter information of 1st distance : \n");
	printf("Enter feet : ");
	fflush(stdin);	fflush(stdout);
	scanf("%d", &gfirst.feet);
	printf("Enter inch : ");
	fflush(stdin);	fflush(stdout);
	scanf("%f", &gfirst.inch);

	printf("Enter information of 2nd distance : \n");
	printf("Enter feet : ");
	fflush(stdin);	fflush(stdout);
	scanf("%d", &gsecond.feet);
	printf("Enter inch : ");
	fflush(stdin);	fflush(stdout);
	scanf("%f", &gsecond.inch);
}

void calculate_sum(void)
{
	//calculate sum
	gsum.feet = gfirst.feet + gsecond.feet;
	gsum.inch = gfirst.inch + gsecond.inch;

	//convert inch to feet
	if(gsum.inch / 12 >= 1)
	{
		gsum.feet += (gsum.inch / 12);
		gsum.inch -= (int)(gsum.inch / 12) * 12;
	}
	printf("Sum of distances =  %d'-%.1f",gsum.feet, gsum.inch);
}
