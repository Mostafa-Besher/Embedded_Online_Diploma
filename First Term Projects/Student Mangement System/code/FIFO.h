/*
 * FIFO.h
 *
 *  Created on: Apr 29, 2021
 *      Author: MostafaBesher
 */

#ifndef FIFO_H_
#define FIFO_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Student_mangement_system.h"

//user configuration
#define fifo_width			50

typedef struct
{
	char first_name[20];
	char last_name[20];
	unsigned int student_id;
	float student_gpa;
	unsigned int course_id;
}element_type;



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

//FIFO APIS
void fifo_init (FIFO_buf_t *p_queue);
FIFO_status enqueue_item (FIFO_buf_t *p_queue, element_type item);
FIFO_status dequeue_item (FIFO_buf_t *p_queue, element_type *p_item);
void fifo_clear (FIFO_buf_t *p_queue);
unsigned int fifo_is_full (FIFO_buf_t *p_queue);
unsigned int fifo_is_empty (FIFO_buf_t *p_queue);
unsigned int fifo_size (FIFO_buf_t *p_queue);
void Traverse_fifo (FIFO_buf_t *p_queue, void (*pf)(element_type));
unsigned int search_queue(FIFO_buf_t *p_queue, element_type key, unsigned int key_type);
void Display (element_type item);
void update_student_id (FIFO_buf_t *p_queue, element_type data, unsigned int new_id);
unsigned int Delete_by_id (FIFO_buf_t *p_queue, unsigned int key);


#endif /* FIFO_H_ */
