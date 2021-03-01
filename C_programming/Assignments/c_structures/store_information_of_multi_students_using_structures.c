/*
 * store_information_of_multi_students_using_structures.c
 *
 *  Created on: Feb 28, 2021
 *      Author: mostafa
 */

#include <stdio.h>
void Enter_students_info(void);
void Displaying_students_info(void);

struct sstudent
{
	char name[20];
	int roll;
	float marks;
};

struct sstudent students_info[10];
int i;

int main()
{
	Enter_students_info();
	Displaying_students_info();
	return 0;
}

void Enter_students_info(void)
{
	printf("Enter information of students : \n");

	for(i = 0; i <10; i++)
	{
		students_info[i].roll = i + 1;
		printf("For roll number %d : \n", students_info[i].roll);
		printf("Enter name : ");
		fflush(stdin);	fflush(stdout);
		scanf("%s", students_info[i].name);
		printf("Enter marks : ");
		fflush(stdin);	fflush(stdout);
		scanf("%f", &students_info[i].marks);
	}
}

void Displaying_students_info(void)
{
	printf("Displaying information of students : \n");

	for(i = 0; i <10; i++)
	{
		printf("Information For roll number %d : \n", students_info[i].roll);
		printf("Name : %s\nMarks : %.2f\n", students_info[i].name, students_info[i].marks);
	}
}
