/*
 * Student_mangement_system.c
 *  Created on: May 26, 2021
 *      Author: mostafa
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Student_mangement_system.h"
#include "FIFO.h"

//global variables
FIFO_buf_t students_list;
element_type student_data;
static unsigned int found = 0;

void student_count()
{
	unsigned int student_count = fifo_size(&students_list);
	printf("[info] The Total Number Of Students is %d\n", student_count);
	printf("[info] You Can Add Up To %d Students\n", fifo_width);
	printf("[info] You Can Add %d More Students\n", fifo_width-student_count);

}

void Display (element_type item)
{
	printf("Student First Name : %s\n", item.first_name);
	printf("Student Last Name : %s\n", item.last_name);
	printf("Student ID : %d\n", item.student_id);
	printf("Student GPA : %.2f\n", item.student_gpa);
	printf("Course ID : %d\n", item.course_id);
	printf("----------------------------\n");
}

void Add_Student_Data()
{
	//check if FIFO id full
	if(fifo_is_full(&students_list))
		printf("Students List Is Full");
	else
	{
		float max_gpa = 4;
		//add student first name
		printf("Enter Student First Name : ");
		fflush(stdin);	fflush(stdout);
		gets(student_data.first_name);
		//add student last name
		printf("Enter Student Last Name : ");
		fflush(stdin);	fflush(stdout);
		gets(student_data.last_name);
		//add student roll number
		do
		{
			printf("Enter Student Roll Number : ");
			fflush(stdin);	fflush(stdout);
			scanf("%d", &student_data.student_id);
			//check if roll number is already exist
			found = search_queue(&students_list, student_data, id);
			if(found)
				printf("[Error]This ID Is Already Exist\n");
		}while(found);
		//add student GPA and check if GPA > 4
		do
		{
			printf("Enter Student GPA : ");
			fflush(stdin);	fflush(stdout);
			scanf("%f", &student_data.student_gpa);
			if(student_data.student_gpa > max_gpa)
				printf("[Error]GPA Should Not Exceed (4)\n");
		}while(student_data.student_gpa > max_gpa);
		//add student selected courses
		printf("Enter Course ID : ");
		fflush(stdin);	fflush(stdout);
		scanf("%d", &student_data.course_id);
		enqueue_item(&students_list, student_data);
		printf("[info] Student Data Is Added Successfully...\n");
		printf("----------------------------\n");
		student_count();
	}
	printf("\n=======================================\n");
}

void find_student_by_id()
{
	printf("Enter Roll Number of Student : ");
	fflush(stdin);	fflush(stdout);
	scanf("%d", &student_data.student_id);
	found = search_queue(&students_list, student_data, id_s);
	if(!found)
	{
		printf("[Error] Roll Number (%d) Not Found", student_data.student_id);
	}
	printf("\n=======================================\n");
}

void find_student_by_fname()
{
	printf("Enter Student First Name : ");
	fflush(stdin);	fflush(stdout);
	gets(student_data.first_name);
	if(!search_queue(&students_list, student_data, first_nam))
	{
		printf("[Error] Student First Name \"%s\" Not Found", student_data.first_name);
	}
	printf("\n=======================================\n");
}

void find_student_by_course_id()
{
	printf("Enter Course ID : ");
	fflush(stdin);	fflush(stdout);
	scanf("%d", &student_data.course_id);
	if(!search_queue(&students_list, student_data, c_id))
	{
		printf("[Error] Course ID (%d) Not Found", student_data.course_id);
	}
	printf("\n=======================================\n");
}

void Delete_student()
{
	if(fifo_is_empty(&students_list))
		printf("Students List Is Empty\n");
	else
	{
		unsigned int search_id = 0;
		printf("Enter Roll Number of Student : ");
		fflush(stdin);	fflush(stdout);
		scanf("%d", &search_id);
		if(Delete_by_id(&students_list, search_id) == 1)
			printf("[info] Student Data Is Deleted Successfully...\n");
	}
}

void update_student_data()
{
	unsigned int update_op;
	printf("Choose Data You Want To Update : \n");
	printf("1. First Name\n");
	printf("2. Last Name\n");
	printf("3. Roll Number\n");
	printf("4. GPA\n");
	printf("5. Course ID\n");
	do
	{
		printf("Enter Roll Number of Student : ");
		fflush(stdin);	fflush(stdout);
		scanf("%d", &student_data.student_id);
		found = search_queue(&students_list, student_data, id);
		if(!found)
		{
			printf("[Error] Roll Number (%d) Not Found\n", student_data.student_id);
		}
	}while(!found);
	printf("Enter Option Number : ");
	fflush(stdin);	fflush(stdout);
	scanf("%d", &update_op);
	if(update_op == 1)
	{
		printf("Enter New First Name : ");
		fflush(stdin);	fflush(stdout);
		gets(student_data.first_name);
		search_queue(&students_list, student_data, update_fname);
		printf("[info] Student Data Updated Successfully\n");
	}

	else if(update_op == 2)
	{
		printf("Enter New Last Name : ");
		fflush(stdin);	fflush(stdout);
		gets(student_data.last_name);
		search_queue(&students_list, student_data, update_lname);
		printf("[info] Student Data Updated Successfully\n");
	}

	else if(update_op == 3)
	{
		unsigned int new_id = 0;
		printf("Enter New Student ID : ");
		fflush(stdin);	fflush(stdout);
		scanf("%d", &new_id);
		update_student_id(&students_list, student_data, new_id);
		printf("[info] Student Data Updated Successfully\n");
	}

	else if(update_op == 4)
	{
		printf("Enter New GPA : ");
		fflush(stdin);	fflush(stdout);
		scanf("%f", &student_data.student_gpa);
		search_queue(&students_list, student_data, update_gpa);
		printf("[info] Student Data Updated Successfully\n");
	}

	else if(update_op == 5)
	{
		printf("Enter New Student Course ID : ");
		fflush(stdin);	fflush(stdout);
		scanf("%d", &student_data.course_id);
		search_queue(&students_list, student_data, update_cid);
		printf("[info] Student Data Updated Successfully\n");
	}
	else
		printf("[Error] Incorrect Option Number");
	printf("\n=======================================\n");

}

void print_all_students_info()
{
	if(fifo_is_empty(&students_list))
		printf("Students List Is Empty");
	else
	{
		printf("All Students Details Are : \n");
		Traverse_fifo(&students_list, Display);
	}

	printf("\n=======================================\n");
}

void Exit_program()
{
	printf("Program Exited Successfully");
	printf("\n=======================================\n");
	exit(1);
}


