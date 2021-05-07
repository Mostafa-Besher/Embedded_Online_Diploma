/*
 * linked_list.c
 *
 *  Created on: May 3, 2021
 *      Author: MostafaBesher
 */


#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>

void list_init(List *plist)
{
	plist ->head = NULL;
	plist ->size = 0;
}

void list_add (List *plist, element_type item)
{
	list_node *p_node, *p_current;
	p_node = (list_node *)malloc(sizeof(list_node));
	p_node ->next = NULL;
	p_node ->data = item;
	//check if adding item in first location
	if(plist ->head == NULL)
	{
		plist ->head = p_node;
	}

	else
	{
		p_current = plist ->head;
		while(p_current ->next)
		{
			p_current = p_current ->next;
		}

		p_node ->next = p_current ->next;
		p_current ->next = p_node;
	}

	plist ->size++;
}

unsigned int list_search (List *plist, element_type key, unsigned int *position)
{
	element_type found;
	list_node * p_search;
	unsigned int pos = 0;
	p_search = plist ->head;
	found.id = (p_search ->data.id);

	while(found.id != key.id && p_search)
	{
		p_search = p_search ->next;
		if(p_search)
		{
			found = (p_search ->data);
			pos++;
		}
	}
	//check if item found
	if(found.id == key.id)
	{
		*position = pos;
		return 1;
	}
	//check if item not found
	else
		return 0;
}


unsigned int list_delete (List *plist, element_type key)
{
	list_node *prev, *temp;
	unsigned int position;
	//if element found
	if(list_search(plist, key, &position))		//call list_search() to search for inserted id
	{
		//check if there is only one element in list
		if(position == 0)
		{
			temp = plist ->head ->next;
			free(plist ->head);
			plist ->head = temp;

		}

		else
		{
			unsigned int i;
			for(i=0, prev = plist ->head; i<position-1; i++)
				prev = prev ->next;

			temp = prev ->next ->next;		//temp pointing to next element
			free(prev ->next);				//delete selected node
			prev ->next = temp;
		}

		plist ->size--;
		return 1;
	}

	else
		return 0;
}


unsigned int Traverse_list (List *plist, void (*pf)(element_type))
{
	list_node * pnode = plist ->head;
	unsigned int i = 1;
	//check if list is not empty
	if(pnode)
	{
		while(pnode)
		{
			printf("Record Number %d\n", i);
			(*pf)(pnode ->data);
			pnode = pnode ->next;
			i++;
		}
		return 1;
	}
	else
		return 0;
}


void destroy_list (List *plist)
{
	list_node  *temp;
	while(plist ->head)
	{
		temp = plist ->head ->next;
		free(plist ->head);
		plist ->head = temp;
	}
}


unsigned int  Retrieve_item (List *plist, unsigned int pos, element_type * pitem)
{
	list_node * pcurrent = plist ->head;
	//check if list is not empty
	if(pcurrent)
	{
		//check if entered position is greater than max valid index
		if(pos >= plist ->size)
		{
			printf("Wrong index !\nPlease insert valid index.\n");
			return 0;
		}

		//check if position equal index of first element
		if(pos == 0)
		{
			*pitem = plist ->head ->data;
		}

		else
		{
			int i;
			for(i=0; i<pos; i++)
				pcurrent = pcurrent ->next;
			*pitem = pcurrent ->data;
		}

		return 1;
	}

	//in case of list is empty
	else
		return 0;


}


unsigned int rec_list_length (list_node *temp)
{
	if(!temp)
		return 0;

	return (1 + rec_list_length (temp ->next));
}


unsigned int list_middle_element (List *plist, element_type *pitem)
{
	list_node * pcurrent = plist ->head;

	//if list is not empty
	if(pcurrent)
	{
		unsigned int i, pos;
		pos = plist ->size / 2;
		for(i=0; i<pos; i++)
			pcurrent = pcurrent ->next;
		*pitem = pcurrent ->data;
		return 1;
	}
	//check if list is empty
	else
	{
		printf("List Is Empty\n");
		return 0;
	}

}


unsigned int get_data_from_end (List *plist, unsigned int pos, element_type * pitem)
{
	list_node *pmain = plist ->head;
	list_node  *pref = plist ->head;
	//if inserted index is greater than size
	if(pos >= plist ->size)
	{
		printf("Wrong index !\nPlease insert valid index.\n");
		return 0;
	}
	//if list is not empty
	if(pmain)
	{
		unsigned int i;
		for(i=0; i<pos+1; i++)
			pref = pref ->next;

		while(pref)
		{
			pref = pref ->next;
			pmain = pmain ->next;
		}
		*pitem = pmain ->data;
		return 1;
	}
	//if list is empty
	else
	{
		printf("List Is Empty\n");
		return 0;
	}
}


void Reverse_list (list_node *temp, element_type *pitem)
{
			/*Using Recursion*/

	//check if list is not empty
	if(temp)
	{
		if(temp ->next)
			Reverse_list(temp ->next, pitem);
		*pitem = temp ->data;
		printf("ID : %d\nName : %s\nHeight : %f\n", pitem ->id, pitem ->name, pitem ->height);
	}
	else
		printf("List Is Empty");
}


unsigned int List_Is_Empty (List *plist)
{
	if(!plist ->head)
		return 1;
	else
		return 0;
}


