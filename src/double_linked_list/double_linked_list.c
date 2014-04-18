/**
 * Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
 *
 */

#include "double_linked_list/double_linked_list.h"

#include "types/types.h"
#include "half_edge/half_edge.h"

#include <stdlib.h>
#include <stdio.h>

struct double_linked_list* init_double_linked_list(item_type type)
{
	struct double_linked_list* list;
	list = (struct double_linked_list*) malloc(sizeof(struct double_linked_list));
	

	if (list == NULL) {
		printf("Ya no hay memoria disponible: init_double_linked_list()\n");
		exit(EXIT_FAILURE);
	}

	list->size = 0;
	list->head = list->tail = NULL;
	list->type = type;

	return list;
}

void destroy_double_linked_list(struct double_linked_list* list)
{
	while(!empty_list(list))
		pop_front(list);

	free(list);
}

void destroy_double_linked_list_with_types(struct double_linked_list* list)
{	
	while (!empty_list(list)) {
		if (list->type == POINT) {
			destroy_point((struct point*)pop_front(list));
		} else if (list->type == HALF_EDGE) {
			destroy_half_edge_with_points((struct half_edge*)pop_front(list));
		}
	}
	
	free(list);
}


int empty_list(struct double_linked_list* list)
{
	if (list == NULL) {
		return TRUE;
	} else if (list->size == 0) {
	 	return TRUE;
	} else {
		return FALSE;
	}
}

struct list_item* init_list_item()
{
	struct list_item* item;
	item = (struct list_item*) malloc(sizeof(struct list_item));
	
	if (item == NULL) {
		printf("Ya no hay memoria disponible: init_list_item()");
		exit(EXIT_FAILURE);
	}

	item->element = NULL;
	item->left = NULL;
	item->right = NULL;
	
	return item;
}

void destroy_list_item(struct list_item* item)
{
	free(item);
}

struct double_linked_list* create_copy_list(struct double_linked_list* list)
{
	struct double_linked_list* copy;
	copy = init_double_linked_list(list->type);
	
	struct list_item* tmp;
	tmp = list->head;
	
	while(tmp != NULL) {
		push_back(copy, tmp->element);
		tmp = tmp->right;
	}

	return copy;
}

void push_back(struct double_linked_list* list,  void* element)
{
	struct list_item *tmp1, *tmp2;

	tmp2 = init_list_item();
	tmp2->element = element;

	
	if (empty_list(list)) {
		list->head = list->tail = tmp2;
		list->size += 1;
		return;
	}
	
	tmp1 = list->tail;
	tmp1->right = tmp2;
	
	tmp2->left = tmp1;
  	list->tail = tmp2;
	list->size += 1;
	return;
}

void push_front(struct double_linked_list* list, void* element)
{
	struct list_item *tmp1, *tmp2;

	tmp2 = init_list_item();

	tmp2->element = element;

	
	if (empty_list(list)) {
		list->head = list->tail = tmp2;
		list->size += 1;
		return;
	}
	
	tmp1 = list->head;
	tmp1->left = tmp2;
	
	tmp2->right = tmp1;
	list->head = tmp2;

	list->size += 1;
	return;
}

void* pop_back(struct double_linked_list* list)
{
	
	if (empty_list(list))
		return NULL;

	struct list_item *tmp1, *tmp2;
	tmp1 = list->tail;
	tmp2 = tmp1->left;
	
	void* element;
	
	list->size -= 1;
	if (list->size == 0) {
		list->head = list->tail = NULL;
	} else {
		tmp2->right = NULL;
		list->tail = tmp2;
	}
	
	element = tmp1->element;
	destroy_list_item(tmp1);
	
	return element;
}

void* pop_front(struct double_linked_list* list)
{
	if (empty_list(list)) 
		return NULL;

	struct list_item *tmp1, *tmp2;
	tmp1 = list->head;	
	tmp2 = tmp1->right;
	
	void* element;
	
	list->size -= 1;
	if (list->size == 0) {
		list->head = list->tail = NULL;
	} else {
		tmp2->left = NULL;
		list->head = tmp2;
	}

	element = tmp1->element;

	destroy_list_item(tmp1);
	return element;
}

void* pick_back(struct double_linked_list* list)
{
	if (empty_list(list))
		return NULL;
	else
		return list->tail->element;
}

void* pick_front(struct double_linked_list* list)
{
	if (empty_list(list))
		return NULL;
	else
		return list->head->element;
}

struct half_edge* cast_half_edge(void* half_edge)
{
        return (struct half_edge*)half_edge;
}

struct point* cast_point(void* point)
{
        return (struct point*)point;
}
