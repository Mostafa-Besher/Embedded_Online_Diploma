/*
 * LIFO.c
 *
 *  Created on: Apr 27, 2021
 *      Author: mostafa
 */

#include "LIFO.h"

void lifo_init (lifo_buf_t *p_stack)
{
	p_stack ->stack_top = p_stack ->stack_buffer;
	p_stack ->no_of_elements = 0;
}

lifo_status push_item (lifo_buf_t *p_stack, element_type item)
{
	//check stack if pointer are valid
	if(!p_stack)
		return stack_null;
	//check stack full
	if(p_stack ->no_of_elements == stack_width)
		return stack_full;

	//push item
	if(p_stack ->no_of_elements == stack_width - 1)		//check critical case when pushing the last item
	{
		*(p_stack ->stack_top) = item;
		p_stack ->no_of_elements++;
	}
	else
	{
		*(p_stack ->stack_top) = item;
		p_stack ->stack_top++;
		p_stack ->no_of_elements++;
	}

	return no_error;
}

lifo_status  pop_item (lifo_buf_t *p_stack, element_type *pitem)
{
	//check stack if pointer are valid
	if(!p_stack)
		return stack_null;
	//check stack empty
	if(p_stack ->no_of_elements == 0)
		return stack_empty;
	//pop item

	if(p_stack ->no_of_elements == stack_width)		//check critical case when stack full
	{
			*pitem = *(p_stack ->stack_top);
			p_stack ->no_of_elements--;
	}

	else
	{
		p_stack ->stack_top--;
		*pitem = *(p_stack ->stack_top);
		p_stack ->no_of_elements--;
	}

	return no_error;
}

void lifo_clear (lifo_buf_t *p_stack)
{
	p_stack ->stack_top = p_stack ->stack_buffer;
	p_stack ->no_of_elements = 0;
}

lifo_status lifo_top  (lifo_buf_t *p_stack, element_type *ptop)
{
	//check stack if pointer are valid
	if(!p_stack)
		return stack_null;
	//check if stack is empty
	if(p_stack ->no_of_elements == 0)
		return stack_empty;
	//get top element
	if(p_stack ->no_of_elements == stack_width)
	{
		*ptop = *(p_stack ->stack_top);
	}
	else
	{
		*ptop = *(p_stack ->stack_top - 1);
	}
	return no_error;

}

unsigned int lifo_size (lifo_buf_t *p_stack)
{
	//check stack if pointer are valid
	if(!p_stack)
		return stack_null;
	return (p_stack ->no_of_elements);
}

void Traverse_lifo (lifo_buf_t *p_stack, void (*pf)(element_type) )
{
	int i ;
	for(i=p_stack ->no_of_elements; i > 0; i--)
	{
		(*pf)(p_stack ->stack_buffer[i - 1]);
	}
}

unsigned int lifo_full (lifo_buf_t *p_stack)
{
	//check stack if pointer are valid
	if(!p_stack)
		return stack_null;
	//check if stack is full
	if(p_stack ->no_of_elements == stack_width)
		return 1;
	else
		return 0;
}

unsigned int lifo_empty (lifo_buf_t *p_stack)
{
	//check stack if pointer are valid
	if(!p_stack)
		return stack_null;
	//check if stack is empty
	if(p_stack ->no_of_elements == 0)
		return 1;
	else
		return 0;

}

