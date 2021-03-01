/*
 * store_information_of_student_using_structure.c
 *
 *  Created on: Feb 28, 2021
 *      Author: mostafa
 */

#include <stdio.h>
void Enter_student_info(void);

struct sstudent
{
	char name[30];
	int roll;
	float marks;
};

struct sstudent gs;

int main()
{
	Enter_student_info();
	printf("\nDisplaying information: \n");
	printf("Name : %s\nRoll : %d\nMarks : %.2f\n",gs.name, gs.roll, gs.marks);
	return 0;
}

void Enter_student_info(void)
{
	printf("Enter information is students: \n");
	printf("Enter name : ");
	fflush(stdin);	fflush(stdout);
	scanf("%s", gs.name);
	printf("Enter roll number : ");
	fflush(stdin);	fflush(stdout);
	scanf("%d", &gs.roll);
	printf("Enter marks : ");
	fflush(stdin);	fflush(stdout);
	scanf("%f", &gs.marks);
}
