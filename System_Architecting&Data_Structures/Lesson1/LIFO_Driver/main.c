/*
 * main.c
 *
 *  Created on: Apr 27, 2021
 *      Author: mostafa
 */

#include "LIFO.h"
#include <stdio.h>
#include <stdlib.h>

void Display (element_type item);

int main()
{
	unsigned int i;
	element_type temp = 0, top_item;
	lifo_buf_t stack1;
	lifo_init(&stack1);

	//pushing items
	for(i=5; i<9; i++)
	{
		push_item(&stack1, i);
		printf("item pushed : %d\n", i);
	}
	printf("==========================\n");
	//display items
	printf("\tDisplay stack items : \n");
	Traverse_lifo (&stack1, Display );
	printf("==========================\n");
	//check if stack is full
	if( lifo_full(&stack1) )
	{
		//pop one item
		printf("if stack is full we popping an item\n");
		pop_item(&stack1, &temp);
		//display items
		printf("\tDisplay stack items : \n");
		Traverse_lifo (&stack1, Display );
		printf("==========================\n");
	}
	//get top item
	lifo_top(&stack1, &top_item);
	printf("stack top item = %d\n", top_item);
	printf("==========================\n");
	//get stack size
	printf("stack1 size = %d\n", lifo_size(&stack1));
	printf("==========================\n");
	//poping items
	printf("poped items : \n");
	for(i=0; i<3; i++)
	{
		pop_item(&stack1, &temp);
		printf("item poped : %d\n", temp);
	}
	printf("==========================\n");
	//display items
	printf("\tDisplay stack items : \n");
	if(lifo_empty(&stack1))
		printf("Lifo Is Empty\n");
	printf("==========================\n");
	//check if stack is empty
	if( lifo_empty(&stack1) )
	{
		printf("if stack is empty we pushing 100\n");
		//push one item
		push_item(&stack1, 100);
		printf("item pushed : 100\n");
		printf("==========================\n");
		printf("\tDisplay stack items : \n");
		Traverse_lifo (&stack1, Display );
	}

	return 0;
}


void Display (element_type item)
{
	printf("item is %d\n", item);
}
