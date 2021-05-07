/*
 * FIFO.h
 *
 *  Created on: Apr 29, 2021
 *      Author: MostafaBesher
 */

#ifndef FIFO_H_
#define FIFO_H_


//user configuration
#define element_type	unsigned int
#define fifo_width			4


//FIFO
typedef struct
{
	element_type fifo_buffer[fifo_width];
	element_type *head;
	element_type *tail;
	unsigned int no_of_elements;
}FIFO_buf_t;

typedef enum
{
	fifo_null,
	fifo_empty,
	fifo_full,
	fifo_no_error
}FIFO_status;

//APIS
void fifo_init (FIFO_buf_t *p_queue);
FIFO_status enqueue_item (FIFO_buf_t *p_queue, element_type item);
FIFO_status dequeue_item (FIFO_buf_t *p_queue, element_type *p_item);
void fifo_clear (FIFO_buf_t *p_queue);
unsigned int fifo_is_full (FIFO_buf_t *p_queue);
unsigned int fifo_is_empty (FIFO_buf_t *p_queue);
unsigned int fifo_size (FIFO_buf_t *p_queue);
void Traverse_fifo (FIFO_buf_t *p_queue, void (*pf)(element_type));

#endif /* FIFO_H_ */
