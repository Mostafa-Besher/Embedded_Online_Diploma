/*
 * LIFO.h
 *
 *  Created on: Apr 27, 2021
 *      Author: mostafa
 */

#ifndef LIFO_H_
#define LIFO_H_

//user configuration
#define element_type	unsigned int
#define stack_width		4

//lifo
typedef struct
{
	element_type  stack_buffer[stack_width];
	element_type  *stack_top;
	unsigned int no_of_elements;
}lifo_buf_t;

typedef enum
{
	no_error,
	stack_full,
	stack_empty,
	stack_null
}lifo_status;


//APIS
void lifo_init (lifo_buf_t *p_stack);
lifo_status push_item (lifo_buf_t *p_stack, element_type item);
lifo_status pop_item (lifo_buf_t *p_stack, element_type *pitem);
void lifo_clear (lifo_buf_t *p_stack);
lifo_status lifo_top  (lifo_buf_t *p_stack, element_type *ptop);
unsigned int lifo_size (lifo_buf_t *p_stack);
void Traverse_lifo (lifo_buf_t *p_stack, void (*pf)(element_type) );
unsigned int lifo_full (lifo_buf_t *p_stack);
unsigned int lifo_empty (lifo_buf_t *p_stack);

#endif /* LIFO_H_ */
