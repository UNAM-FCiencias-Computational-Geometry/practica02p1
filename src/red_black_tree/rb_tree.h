/**
 * Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
 *
 * Description:
 * Contiene la estructura que representa un red-black tree para ordenar puntos
 * respecto a la coordenada que se le indique, x o y.
 # En el archivo main.c viene un ejemplo de como crear un rb-tree.
 */

#ifndef RB_TREE_H_
#define RB_TREE_H_

#include "points/2d_points.h"

/** Enumerador que sirve para representar el color de los nodos del arbol. */
typedef enum {RED = 1, BLACK} color;

/** 
 * Enumerador que sirve para representar la coordenada por la cual se ordena
 * el arbol. */
typedef enum {X = 1,Y} coordinate;

/**
 *         parent
 *          /
 *       rb_node [color,point]      
 *        /   \         
 *      left right
 */
struct rb_node {
	struct rb_node* left;
	struct rb_node* right;
	struct rb_node* parent;
	
	color color;	

	struct point* point;
};

/**
   Apuntador asi el nodo raiz y la coordenada por la cual se ordena.
*/
struct rb_tree {
	struct rb_node* root;
	coordinate coordinate;
};

/**
 * Cambiamos la constante NULL, por un nodo sentinela, esto sirve para tener
 * mas libertad en la implementacion de insert_fixup y delete_fixup.
 */
extern struct rb_node sentinel;

/** 
 * Inicializa un rb-tree que ordena puntos a partir de la coordenada que se le
 * pase.
*/
struct rb_tree* init_rb_tree(coordinate);

/** Destruye el arbol que se le pase, no destruye los puntos.*/
void destroy_rb_tree(struct rb_tree*);

/** Inicializa un nodo. */
struct rb_node* init_rb_node();

/** Destruye un nodo. */
void destroy_rb_node(struct rb_node*);

/** Inseta un punto al rb-tree, puede estar repetido y sigue funcionando. */
void rb_insert(struct rb_tree*,struct point*);

/** 
 * Busca el punto que se le pasa.
 */
struct point* rb_search(struct rb_tree*, struct point*);

/** 
 * Borra el punto que se le pasa
 */
struct point* rb_delete(struct rb_tree*, struct point*);

/** 
 * Regresa el punto que tenga coordenada menor/mayor X o Y, dependiendo
 * de cual se le indico al momento de crear el arbol.
 */
struct point* rb_min(struct rb_tree*);
struct point* rb_max(struct rb_tree*);

#endif
