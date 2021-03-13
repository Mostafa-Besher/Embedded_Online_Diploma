/*
 * show_content_of_array_which_is_pointer_to_structure.c
 *
 *  Created on: Mar 12, 2021
 *      Author: mostafa
 */
#include <stdio.h>

struct Employee
{
	char *name;
	int id;
}Emp1, Emp2;

int main()
{
	Emp1.id = 1002;
	Emp1.name = "Alex";

	Emp2.id = 1003;
	Emp2.name = "John";

	int i;
	struct Employee *p1 = &Emp1, *p2 = &Emp2;
	struct Employee (* arr[]) = {p1, p2};
	struct Employee (*(*prr)[2]) = &arr;

	for(i = 0; i < 2; i++)
	{
		printf("Employee Name : %s\nEmployee ID : %d\n\n", (**prr + i)->name, (**prr + i)->id);
	}
	return 0;
}

