/*
 * main.c
 *
 *  Created on: Apr 29, 2021
 *      Author: MostafaBesher
 */

#include "FIFO.h"
#include <stdio.h>
void Display (element_type item);

int main()
{
	FIFO_buf_t queue1;
	unsigned int i;
	element_type temp;
	fifo_init(&queue1);
	//enqueue items
	for(i=0; i<3; i++)
	{
		if(enqueue_item(&queue1, i) == fifo_no_error)
		printf("item enqueued = %d\n", i);
	}
	printf("===========================\n");
	//display items
	printf("\tDisplay queue1 items : \n");
	Traverse_fifo(&queue1, Display);
	printf("===========================\n");
	//display size
	printf("\nfifo size = %d\n", fifo_size(&queue1));
	printf("===========================\n");
	//dequeue one item
	if(dequeue_item(&queue1, &temp) == fifo_no_error)
		printf("\nitem dequeued = %d\n", temp);
	printf("===========================\n");
	//display items
	printf("\tDisplay queue1 items : \n");
	Traverse_fifo(&queue1, Display);
	printf("===========================\n");
	//enqueue one item
	if(enqueue_item(&queue1, 100) == fifo_no_error)
		printf("item enqueued = %d\n", 100);
	printf("===========================\n");
	//display items
	printf("\tDisplay queue1 items : \n");
	Traverse_fifo(&queue1, Display);
	printf("===========================\n");
	//dequeue all items
	printf("dequeue items : \n");
	for(i=0; i<1; i++)
	{
		if(dequeue_item(&queue1, &temp) == fifo_no_error)
		printf("item dequeued = %d\n", temp);
	}
	printf("===========================\n");
	printf("\tDisplay queue1 items : \n");
	Traverse_fifo(&queue1, Display);
	printf("===========================\n");
	printf("Clear queue 1\n");
	fifo_clear(&queue1);
	//display items
	printf("\tDisplay queue1 items : \n");
	if(!fifo_is_empty(&queue1))
	{
		Traverse_fifo(&queue1, Display);
		printf("===========================\n");
	}
	else
	{
		printf("Fifo Is Empty\n");
		printf("===========================\n");
	}

	return 0;
}

void Display (element_type item)
{
	printf("item is %d\n", item);
}
