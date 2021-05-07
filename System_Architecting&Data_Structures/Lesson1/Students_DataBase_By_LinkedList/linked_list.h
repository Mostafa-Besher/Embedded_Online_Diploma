/*
 * linked_list.h
 *
 *  Created on: May 3, 2021
 *      Author: MostafaBesher
 */

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

//user configuration
typedef struct
{
	unsigned int id;
	char name[40];
	float height;
}element_type;


//list node
typedef struct node
{
	element_type data;
	struct node *next;

}list_node;


//list
typedef struct list
{
	list_node *head;
	unsigned int size;
}List;


//APIS
void list_init(List *plist);
void list_add (List *plist, element_type item);
unsigned int list_delete (List *plist, element_type key);
unsigned int list_search (List *plist, element_type key, unsigned int *position);
unsigned int Traverse_list (List *plist, void (*pf)(element_type));
void destroy_list (List *plist);
unsigned int  Retrieve_item (List *plist, unsigned int pos, element_type * pitem);
unsigned int rec_list_length (list_node *temp);
unsigned int list_middle_element (List *plist, element_type *pitem);
unsigned int get_data_from_end (List *plist, unsigned int pos, element_type * pitem);
void Reverse_list (list_node *temp, element_type *pitem);
unsigned int List_Is_Empty (List *plist);


#endif /* LINKED_LIST_H_ */
