/*
 * main.c
 *
 *  Created on: May 3, 2021
 *      Author: MostafaBesher
 */

#include <stdio.h>
#include "string.h"
#include "linked_list.h"
void Display(element_type student_data);

int main()
{
	List students_list;
	list_init(&students_list);
	element_type student_data;
	unsigned int option_num;
	while(1)
	{
		printf("==================================\n");
		printf("\t\t\t choose of the following options\n");
		printf("1: Add student\n2: Delete student\n3: View students\n4: Delete all\n");
		printf("5: Get Student Data\n6: List Length\n7: Middle List Student\n");
		printf("8: Get Student From The List End\n9: Reverse List\n");
		printf("Enter option number : ");
		fflush(stdin);	fflush(stdout);
		scanf("%d", &option_num);
		printf("\n==================================\n");

		if(option_num == 1)
		{
			printf("Enter student ID :");
			fflush(stdin);	fflush(stdout);
			scanf("%d", &student_data.id);
			printf("\nEnter student Full Name :");
			fflush(stdin);	fflush(stdout);
			gets(student_data.name);
			printf("\nEnter student Height :");
			fflush(stdin);	fflush(stdout);
			scanf("%f", &student_data.height);
			list_add(&students_list, student_data);
			printf("\n==================================\n");
		}

		else if(option_num == 2)
		{
			if( !List_Is_Empty(&students_list) )
			{
				printf("Enter student ID To Be Deleted :");
				fflush(stdin);	fflush(stdout);
				scanf("%d", &student_data.id);
				if( list_delete(&students_list, student_data) )
					printf("Record Deleted successfully...\n");
				else
					printf("ID Not Found !\n");
			}

			else
				printf("List Is Empty\n");
			printf("\n==================================\n");
		}

		else if(option_num == 3)
		{
			printf("\t\t\tStudents List\n");
			if( !Traverse_list(&students_list, Display) )
			{
				printf("List Is Empty\n");
			}
			printf("\n==================================\n");
		}

		else if(option_num == 4)
		{
			if( !List_Is_Empty(&students_list) )
			{
				destroy_list(&students_list);
				printf("All Records Deleted");
			}

			else
				printf("List Is Empty\n");
			printf("\n==================================\n");
		}

		else if(option_num == 5)
		{
			if( !List_Is_Empty(&students_list) )
			{
				unsigned int pos;
				//element_type student_data;
				printf("Enter Item Index : ");
				fflush(stdin);	fflush(stdout);
				scanf("%d", &pos);
				if( Retrieve_item(&students_list, pos, &student_data) )
					Display(student_data);
			}

			else
				printf("List Is Empty\n");
			printf("\n==================================\n");
		}

		else if(option_num == 6)
		{
			printf("List Length : %d\n", rec_list_length(students_list.head));
			printf("\n==================================\n");
		}


		else if (option_num == 7)
		{
			if( list_middle_element(&students_list, &student_data) )
				Display(student_data);
			printf("\n==================================\n");
		}

		else if (option_num == 8)
		{
			if( !List_Is_Empty(&students_list) )
			{
				unsigned int pos;
				printf("Enter Item Index : ");
				fflush(stdin);	fflush(stdout);
				scanf("%d", &pos);
				if( get_data_from_end (&students_list, pos, &student_data) )
					Display(student_data);
			}

			else
				printf("List Is Empty\n");
			printf("\n==================================\n");

		}

		else if (option_num == 9)
		{
			if( !List_Is_Empty(&students_list) )
				Reverse_list(students_list.head, &student_data);
			else
				printf("List Is Empty\n");
			printf("\n==================================\n");
		}

		else
		{
			printf("Wrong option Number !\n");
		}
	}

	return 0;
}


void Display(element_type student_data)
{
	printf("ID : %d\nName : %s\nHeight : %f\n", student_data.id, student_data.name, student_data.height);
}
