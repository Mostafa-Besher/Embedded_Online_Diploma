/*
 * main.c

 *
 *  Created on: May 23, 2021
 *      Author: mostafa
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FIFO.h"
#include "Student_mangement_system.h"

extern FIFO_buf_t students_list;

int main()
{
	fifo_init(&students_list);
	unsigned int option_num;
	printf("\t\t\t\t\t>----------Welcome To The Student Management System----------<\n");
	while(1)
	{
		printf("=======================================\n");
		printf("Choose The Task You Want To Perform : \n");
		printf("1. Add Student Data Manually\n");
		printf("2. Find Student Details By Roll Number\n");
		printf("3. Find Student Details By First Name\n");
		printf("4. Find Student Details By Course ID\n");
		printf("5. Find The Total Number Of Students\n");
		printf("6. Delete Student Details By Roll Number\n");
		printf("7. Update Student Details By Roll Number\n");
		printf("8. Show All Information\n");
		printf("9. Exit\n");
		printf("Enter option number : ");
		fflush(stdin);	fflush(stdout);
		scanf("%d", &option_num);
		printf("\n=======================================\n");

		//Add Student Data Manually
		if(option_num == 1)
		{
			Add_Student_Data();
		}
		//Find Student Details By Roll Number
		else if(option_num == 2)
		{
			find_student_by_id();
		}
		//Find Student Details By First Name
		else if(option_num == 3)
		{
			find_student_by_fname();
		}
		//Find Student Details By Course ID
		else if(option_num == 4)
		{
			find_student_by_course_id();
		}
		//Find The Total Number Of Students
		else if(option_num == 5)
		{
			student_count();
		}
		//Delete Student Details By Roll Number
		else if(option_num == 6)
		{
			Delete_student();
		}
		//Update Student Details By Roll Number
		else if(option_num == 7)
		{
			update_student_data();
		}

		//Show All Information
		else if(option_num == 8)
		{
			print_all_students_info();
		}
		//EXIT
		else if(option_num == 9)
		{
			Exit_program();
		}
		else
		{
			printf("Incorrect Option Number\n");
		}
	}
	return 0;
}
