/**
 * Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
 *
 * Description:
 * Una lista doblemente ligada que sirve como stack y como queue.
 * Sirve para tener listas de puntos o segmentos, se le indica 
 * al inicar la lista.
 * Se usa solo para representar conjuntos de puntos o segmentos con direccion.
 */

#ifndef DOUBLE_LINKED_LIST_H_
#define DOUBLE_LINKED_LIST_H_

#include "types/types.h"

/*
 *  |-----------|   left |-----------|  right |-----------|
 *  |           | <----- | list_item | -----> |           |
 *  |-----------|        |-----------|        |-----------|
 **/
struct list_item {
	/** Apunto de cualquier tipo para representar puntos o segmentos, para
		obtener la estructura original debes de hacer un cast. */
	void* element;
	struct list_item* left;
	struct list_item* right;   	
};

/*
 * |------------|                     |------------|
 * |    head    | ----->  .... <----- |    tail    |
 * |------------|                     |------------|
 **/
struct double_linked_list {
	struct list_item* head;
	struct list_item* tail;

	/** Numero de elementos que tiene dentro la lista. */
	int size;
	
	/**
	 *Tipo de dato que guarda la lista:  POINT o HALF_EDGE, viene declarado
	 * dentro del header types/types.h
	 */
	item_type type;
};


/** Inicializa una lista con sus apuntadores nulos. */
struct double_linked_list* init_double_linked_list(item_type);

/** Destruye una lista liberando la memoria de sus elementos. */
void destroy_double_linked_list(struct double_linked_list*);

/**
 * Destruye una lista liberando la memoria de sus elementos y los puntos o
 * segmentos que guarde la lista.
 */
void destroy_double_linked_list_with_types(struct double_linked_list*);

/* Inicializa un elemento de la lista. **/
struct list_item* init_list_item(void);

/* Destruye solo un elemento de la lista. **/
void destroy_list_item(struct list_item*);

/** Hace una copia de la lista dada, sin hacer copia de los elementos. */
struct double_linked_list* create_copy_list(struct double_linked_list*);

/* Indica si la lista que se le pasa esta vacía. **/
int empty_list(struct double_linked_list*);

/* Agrega un nuevo punto o segmento al frente o hasta el final de la lista. **/
void push_back(struct double_linked_list*,void*);
void push_front(struct double_linked_list*,void*);

/**
 * Quita un punto o segmento al frente o hasta el final de la lista, regresa nulo
 * si la lista esta vacia. El apuntador que regresa esta funcion debe de castearse
 * antes de ser usado en otra funcion.
 */
void* pop_back(struct double_linked_list*);
void* pop_front(struct double_linked_list*);

/**
 * Regresa el punto o segmento que esta al frente o al final de la lista.
 * El apuntador que regresa esta funcion debe de castearse anrtes de ser usado
 * en otra funcion.
 */
void* pick_back(struct double_linked_list*);
void* pick_front(struct double_linked_list*);

/**
 * Funciones que hacen casting de los elemetos, usadas para los tests de ruby.
 */
struct half_edge* cast_half_edge(void*);
struct point* cast_point(void*);
#endif
