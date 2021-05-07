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
	//check if fifo is not empty
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
