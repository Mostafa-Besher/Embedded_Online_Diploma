/*
 * FIFO.c
 *
 *  Created on: Apr 29, 2021
 *      Author: MostafaBesher
 */

#include "FIFO.h"

void fifo_init (FIFO_buf_t *p_queue)
{
	p_queue ->head = p_queue ->fifo_buffer;
	p_queue ->tail = p_queue ->fifo_buffer;
	p_queue ->no_of_elements = 0;
}

FIFO_status enqueue_item (FIFO_buf_t *p_queue, element_type item)
{
	//check if pointers are valid
	if(!p_queue ->head || !p_queue ->tail)
		return fifo_null;
	//check if queue is full
	if(p_queue ->no_of_elements == fifo_width)
		return fifo_full;

	//enqueue items
	*(p_queue ->head) = item;
	p_queue ->no_of_elements++;
	//check if head reached last element in queue_buffer
	if( (p_queue ->head) == &(p_queue ->fifo_buffer[fifo_width - 1]) )
		p_queue ->head = p_queue ->fifo_buffer;		//head pointing to first element
	else
		p_queue ->head++;


	return fifo_no_error;
}

FIFO_status dequeue_item (FIFO_buf_t *p_queue, element_type *p_item)
{
	//check if pointers are valid
	if(!p_queue ->head || !p_queue ->tail)
		return fifo_null;
	//check if queue is empty
	if(p_queue ->no_of_elements == 0)
		return fifo_empty;

	//dequeue items
	*p_item =  *(p_queue ->tail);
	p_queue ->no_of_elements--;
	//check if tail reached last element in queue_buffer
	if( (p_queue ->tail) == &(p_queue ->fifo_buffer[fifo_width - 1]) )
		p_queue ->tail = p_queue ->fifo_buffer;		//tail pointing to first element
	else
		p_queue ->tail++;

	return fifo_no_error;
}

void fifo_clear (FIFO_buf_t *p_queue)
{
	p_queue ->head = p_queue ->fifo_buffer;
	p_queue ->tail = p_queue ->fifo_buffer;
	p_queue ->no_of_elements = 0;
}

unsigned int fifo_is_full (FIFO_buf_t *p_queue)
{
	//check if pointers are valid
	if(!p_queue ->head || !p_queue ->tail)
		return fifo_null;
	//check if stack is full
	if(p_queue ->no_of_elements == fifo_width)
		return 1;
	else
		return 0;
}

unsigned int fifo_is_empty (FIFO_buf_t *p_queue)
{
	//check if pointers are valid
	if(!p_queue ->head || !p_queue ->tail)
		return fifo_null;
	//check if stack is empty
	if(p_queue ->no_of_elements == 0)
		return 1;
	else
		return 0;
}

unsigned int fifo_size (FIFO_buf_t *p_queue)
{
	//check if pointers are valid
	if(!p_queue ->head || !p_queue ->tail)
		return fifo_null;
	//return size
	return (p_queue ->no_of_elements);
}

void Traverse_fifo (FIFO_buf_t *p_queue, void (*pf)(element_type))
{
	//check if FIFO is not empty
	if(p_queue ->no_of_elements != 0)
	{
		element_type *temp;
		temp = p_queue ->tail;
		do
		{
			(*pf)(*temp);
			//check if temp reached last location of stack_buffer
			if(temp == &(p_queue ->fifo_buffer[fifo_width - 1]) )
				temp = p_queue ->fifo_buffer;
			else
				temp++;

		}while(temp != p_queue ->head);
	}
}


unsigned int search_queue(FIFO_buf_t *p_queue, element_type key, unsigned int key_type)
{
	unsigned int found = 0;
	unsigned int no_found = 0;
	//check if FIFO is not empty
	if(p_queue ->no_of_elements != 0)
	{
		element_type *temp;
		temp = p_queue ->tail;
		do
		{
			//search for student first name
			if(key_type == first_nam )
			{
				if(!strcmp(key.first_name,temp->first_name))
				{
					no_found = 1;
					printf("Student Details Are : \n");
					Display(*temp);
				}

				if(no_found && (temp+1)==p_queue ->head)
					found = 1;

			}
			//search for student roll number
			if(key_type == id )
			{
				if(key.student_id == temp->student_id)
					found = 1;
				else
					found = 0;
			}
			//search for student GPA
			if(key_type == gpa )
			{
				if(key.student_gpa == temp->student_gpa)
					found = 1;
				else
					found = 0;
			}
			//search for student course id
			if(key_type == c_id )
			{
				if(key.course_id == temp->course_id)
				{
					no_found = 1;
					printf("Student Details Are : \n");
					Display(*temp);
				}

				if(no_found && (temp+1)==p_queue ->head)
					found = 1;
			}
			//search for student roll number and print student data
			if(key_type == id_s )
			{
				if(key.student_id == temp->student_id)
				{
					found = 1;
					printf("Student Details Are : \n");
					Display(*temp);
				}
				else
					found = 0;
			}
			//update student first name
			if(key_type == update_fname)
			{
				if(key.student_id == temp->student_id)
				{
					found = 1;
					strcpy(temp ->first_name, key.first_name);
				}
				else
					found = 0;
			}
			//update student last name
			if(key_type == update_lname)
			{
				if(key.student_id == temp->student_id)
				{
					found = 1;
					strcpy(temp ->last_name, key.last_name);
				}
				else
					found = 0;
			}
			//update student GPA
			if(key_type == update_gpa)
			{
				if(key.student_id == temp->student_id)
				{
					found = 1;
					temp ->student_gpa = key.student_gpa;
				}
				else
					found = 0;
			}
			//update student course id
			if(key_type == update_cid)
			{
				if(key.student_id == temp->student_id)
				{
					found = 1;
					temp ->course_id = key.course_id;
				}
				else
					found = 0;
			}

			//check if temp reached last location of stack_buffer
			if(temp == &(p_queue ->fifo_buffer[fifo_width - 1]) )
				temp = p_queue ->fifo_buffer;
			else
				temp++;

		}while(temp != p_queue ->head && found == 0);
	}

	return found;
}


void update_student_id (FIFO_buf_t *p_queue, element_type data, unsigned int new_id)
{
	element_type *temp;
	unsigned int found = 0;
	temp = p_queue ->tail;
	do
	{
		if(data.student_id == temp->student_id)
		{
			temp->student_id = new_id;
		}

		//check if temp reached last location of stack_buffer
		if(temp == &(p_queue ->fifo_buffer[fifo_width - 1]) )
			temp = p_queue ->fifo_buffer;
		else
			temp++;

	}while(temp != p_queue ->head && found == 0);
}

unsigned int Delete_by_id (FIFO_buf_t *p_queue, unsigned int key)
{
	element_type *p_search;
	unsigned int found = 0;
	//p_search = p_item;
	//check if pointers are valid
	if(!p_queue ->head || !p_queue ->tail)
		return fifo_null;
	//check if queue is empty
	if(p_queue ->no_of_elements == 0)
		return fifo_empty;
	//search for id
	p_search = p_queue ->tail;
	do
	{
		if(key == p_search->student_id)
				found = 1;
		else
				found = 0;

		//check if p_search reached last location of stack_buffer
		if(p_search == &(p_queue ->fifo_buffer[fifo_width - 1]) )
			p_search = p_queue ->fifo_buffer;
		else
			p_search++;

	}while(p_search != p_queue ->head && found == 0);
	//dequeue items
	//if id is found
	if(found)
	{
		//when found id in last element in fifo_buffer
		if(p_search == p_queue ->fifo_buffer)
			p_search = &(p_queue ->fifo_buffer[fifo_width - 1]);
		else
			p_search--;

		p_queue ->no_of_elements--;					//decrease FIFO size by one
		//check if deleting the first element
		if(p_search == p_queue ->tail)
		{
			//check if tail points to the last element in fifo_buffer
			if(p_search == &(p_queue ->fifo_buffer[fifo_width - 1]))
				p_queue ->tail = p_queue ->fifo_buffer;
			else
				p_queue ->tail++;
		}
		else
		{
			while(p_search != p_queue ->tail)
			{
				*p_search = *(p_search - 1);
				p_search--;
			}
			p_queue ->tail++;
		}
	}

	//if id not found
	else
		printf("[Error] This Roll Number Is Not Found\n");
	return found;
}





