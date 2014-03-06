#include "red_black_tree/rb_tree.h"

#include <stdio.h>
#include <stdlib.h>


/** 
 * Se crea al momento de compilacion el nodo sentinal que se menciona en el
 * encabezado. */
struct rb_node sentinel = {NULL,NULL,NULL,BLACK,NULL};

/**  Verifica si el arbol que se le pase esta vacio o no.*/
int empty_rb_tree(struct rb_tree* tree)
{
	return tree->root == &sentinel;
}

/**
 * Dependiendo de cual sea la coordenada que se esta comparado, regresa
 * (a->x > b->x) o (a->y > b->y)
*/
int rb_great_than(coordinate coordinate, struct point* a, struct point* b)
{
	if (coordinate == X)
		return (a->x > b->x);
	else
		return (a->y > b->y);
}

/**
 * Dependiento de cual sea la coordenada que se esta comparado, regresa
 * (a->x < b->x) o (a->y < b->y)
 */
int rb_less_than(coordinate coordinate, struct point* a, struct point* b)
{
	if (coordinate == X)
		return (a->x < b->x);
	else
		return (a->y < b->y);
}


/**
 * Toma el nodo tmp1 y le aplica una rotacion hacia la izquierda.
 *
 *     tmp1                   tmp2
 *     / \                    /	\
 *	  *  tmp2        -->    tmp1 *
 *       / \                / \
 *      c   *              *   c
 */
void left_rotate(struct rb_tree* tree, struct rb_node* node)
{
	struct rb_node *tmp1, *tmp2;
	tmp1 = node;
	tmp2 = node->right;
	
	tmp1->right = tmp2->left;
	
	if (tmp2->left != &sentinel) 
		tmp2->left->parent = tmp1;

	tmp2->parent = tmp1->parent;

	if (tmp1->parent == &sentinel) {
		tree->root = tmp2;
	} else if (tmp1 == tmp1->parent->left) {
		tmp1->parent->left = tmp2;
	} else {
		tmp1->parent->right = tmp2;
	}

	tmp2->left = tmp1;
	tmp1->parent = tmp2;
}

/** Toma el nodo tmp1 y le aplica una rotacion hacia la derecha .
 *
 *     tmp1             tmp2
 *     / \              / \
 *   tmp2 *    -->     * tmp1
 *   / \                  /	\
 *	*   c                c   *
 */
void right_rotate(struct rb_tree* tree, struct rb_node* node)
{
	struct rb_node *tmp1, *tmp2;
	tmp1 = node;
	tmp2 = node->left;

	tmp1->left = tmp2->right;

	if (tmp2->right != &sentinel)
		tmp2->right->parent = tmp1;

	tmp2->parent = tmp1->parent;

	if (tmp1->parent == &sentinel) {
		tree->root = tmp2;
	} else if(tmp1 == tmp1->parent->left) {
		tmp1->parent->left = tmp2;
	} else {
		tmp1->parent->right = tmp2;
	}
	
	tmp2->right = tmp1;
	tmp1->parent = tmp2;
}

/**
 * Compone el arbol una vez que se inserta un nodo como hoja y descompone
 * las propiedades del arbol.
 */
void rb_insert_fixup(struct rb_tree* tree, struct rb_node* node)
{

	struct rb_node *tmp1, *tmp2;
	tmp1 = node;

	while (tmp1->parent->color == RED) {
		/** El padre de node es hijo izquierdo. */
		if (tmp1->parent == tmp1->parent->parent->left) {
			
			/** tmp es el tío derecho del padre de node*/
			tmp2 = tmp1->parent->parent->right;
			
			/** Caso 1: tmp tiene color rojo. */
			if (tmp2->color == RED) {
				
				tmp1->parent->color = BLACK;
				tmp2->color = BLACK;
				tmp1->parent->parent->color = RED;
				
				tmp1 = tmp1->parent->parent;
				
			} else {
				/** Caso 2: tmp tiene color negro y node es hijo derecho.
				 *  convertimos el caso 2 en el caso 3.
				 */
				if ( tmp1 == tmp1->parent->right) {
					tmp1 = tmp1->parent;
					left_rotate(tree, tmp1);
				}

				/** Caso 3: tmp tiene color negro y node es hujo izquierdo.*/
				tmp1->parent->color = BLACK;
				tmp1->parent->parent->color = RED;

				right_rotate(tree,tmp1->parent->parent);
			}

		} else {
			/** tmp es el tío izquierdo del padre de node.*/
			tmp2 = tmp1->parent->parent->left;

			/** Caso 1: tmp tiene color rojo*/
			if (tmp2->color == RED) {
				
				tmp1->parent->color = BLACK;
				tmp2->color = BLACK;
				tmp1->parent->parent->color = RED;
				
				tmp1 = tmp1->parent->parent;
				
			} else {
				/** Caso 2: tmp tiene color negro y node es hijo izquierdo.
				 *  convertimos el caso 2 en el caso 3.
				 */
				if ( tmp1 == tmp1->parent->left) {
					tmp1 = tmp1->parent;
					right_rotate(tree, tmp1);
				}

				/** Caso 3: tmp tiene color negro y node es hujo derecho.*/
				tmp1->parent->color = BLACK;
				tmp1->parent->parent->color = RED;

				left_rotate(tree,tmp1->parent->parent);
			}

		}
	}

	tree->root->color = BLACK;
}

/** 
 * Coloca al nodo b como hijo del padre de a y le indica al nodo
 * b que su padre cambio, al nodo a no le dice que su padre ya 
 * no hace referencia
 */
void rb_transplant(struct rb_tree* tree, struct rb_node* a,struct rb_node* b)
{
	if (a->parent == &sentinel) {
		tree->root = b;
	} else if (a == a->parent->left) {
		a->parent->left = b;
	} else {
		a->parent->right = b;
	}
	
	b->parent = a->parent;
}

/**
 * Busca un un nodo en el arbol que contenga exactamente el punto que se le paso.
 **/
struct rb_node* rb_node_search(struct rb_tree* tree, struct point* point)
{
	struct rb_node* tmp;
	tmp = tree->root;

	while(tmp != &sentinel) {
		if (points_equals(tmp->point,point)) {
			break;
		} else if(rb_less_than(tree->coordinate, tmp->point ,point)) {
			tmp = tmp->right;
		} else {
			tmp = tmp->left;
		}
	}
	
	if (tmp == &sentinel)
		return NULL;

	return tmp;
}

/**
 * Compone las propiedades del arbol una vez que el nodo que se le paso se
 * borra.
 */
void rb_delete_fixup(struct rb_tree* tree, struct rb_node* node)
{
	struct rb_node *tmp1, *tmp2;
	tmp1 = node;
	
	while ((tmp1 != tree->root) && (tmp1->color == BLACK)) {
		
		if (tmp1 == tmp1->parent->left) {
			tmp2 = tmp1->parent->right;
			
			if (tmp2->color == RED) {
			
				tmp2->color = BLACK;
				tmp1->parent->color = RED;
				
				left_rotate(tree,tmp1->parent);
				tmp2 = tmp1->parent->right;
			}
			
			
			if ((tmp2->left->color == BLACK) && (tmp2->right->color == BLACK)) {
				
				tmp2->color = RED;
				tmp1 = tmp1->parent;
				
			} else {
				if (tmp2->right->color == BLACK) {
					
					tmp2->left->color = BLACK;
					tmp2->color = RED;
					right_rotate(tree,tmp2);
					tmp2 = tmp1->parent->right;					
				}
				
				tmp2->color = tmp1->parent->color;
				tmp1->parent->color = BLACK;
				tmp2->right->color = BLACK;
				
				left_rotate(tree,tmp1->parent);
				tmp1 = tree->root;
			}
		} else {
			tmp2 = tmp1->parent->left;
			
			if (tmp2->color == RED) {
				
				tmp2->color = BLACK;
				tmp1->parent->color = RED;
				
				right_rotate(tree,tmp1->parent);
				tmp2 = tmp1->parent->left;
			}
			
			if ((tmp2->right->color == BLACK) && (tmp2->left->color == BLACK)) {
				
				tmp2->color = RED;
				tmp1 = tmp1->parent;
				
			} else {
				if (tmp2->left->color == BLACK) {
					
					tmp2->right->color = BLACK;
					tmp2->color = RED;
					left_rotate(tree,tmp2);
					tmp2 = tmp1->parent->left;					
				}
				
				tmp2->color = tmp1->parent->color;
				tmp1->parent->color = BLACK;
				tmp2->left->color = BLACK;
				
				right_rotate(tree,tmp1->parent);
				tmp1 = tree->root;
			}
			
		}
	}
	tmp1->color = BLACK;
}

/**
 * Regresa el nodo que tenga el punto con la menor coordenada X o Y.
 */
struct rb_node* rb_min_node(struct rb_node* node)
{
	struct rb_node* tmp = node;

	if (tmp == NULL)
		return NULL;

	if (tmp == &sentinel)
		return tmp;

	while(tmp->left != &sentinel)
		tmp = tmp->left;

	return tmp;
}

/**
 * Regresa el nodo que tenga el punto con la mayor coordenada X o Y.
 */
struct rb_node* rb_max_node(struct rb_node* node)
{
	struct rb_node* tmp = node;
	
	if (tmp == NULL)
		return NULL;

	if (tmp == &sentinel)
		return tmp;

	while(tmp->right != &sentinel)
		tmp = tmp->right;
	
	return tmp;
}


struct rb_tree* init_rb_tree(coordinate coordinate)
{
	struct rb_tree* tree;
	tree = (struct rb_tree*) malloc(sizeof(struct rb_tree));

	if (tree == NULL) {
		printf("Ya no hay memoria disponible: init_rb_tree()\n");
		exit(EXIT_FAILURE);
	}

	tree->root = &sentinel;
	tree->coordinate = coordinate;

	return tree;
}

void destroy_rb_tree(struct rb_tree* tree)
{
	if (tree == NULL)
		return;
	
	while (!empty_rb_tree(tree))
		rb_delete(tree,rb_min(tree));
	
	free(tree);
}

struct rb_node* init_rb_node(){
	struct rb_node* node;
	node = (struct rb_node*) malloc(sizeof(struct rb_node));
	
      	if (node == NULL) {
		printf("Ya no hay memoria disponible: init_rb_node()\n");
		exit(EXIT_FAILURE);
	}

	node->left = node->right = node->parent = &sentinel;
	node->color = RED;
	
	node->point = NULL;

	return node;
}

void destroy_rb_node(struct rb_node* node)
{
	if (node != NULL && node != &sentinel)
		free(node);
}





void rb_insert(struct rb_tree* tree, struct point* point)
{
	struct rb_node *tmp1, *tmp2;
	tmp1 = tree->root;
	tmp2 = &sentinel;
	
	while (tmp1 != &sentinel) {
		tmp2 = tmp1;	   
		
		if (rb_less_than(tree->coordinate, point, tmp1->point))
			tmp1 = tmp1->left;
		else
			tmp1 = tmp1->right;
	}

	struct rb_node* node;
	node = init_rb_node();
	
	node->parent = tmp2;
	node->point = point;

	if (tmp2 == &sentinel) {
		tree->root = node;
	} else if (rb_less_than(tree->coordinate,point, tmp2->point)) {
		tmp2->left = node;
	} else {
		tmp2->right = node;
	}	

	rb_insert_fixup(tree,node);
}



struct point* rb_search(struct rb_tree* tree, struct point* point)
{
	struct rb_node* tmp = rb_node_search(tree,point);

	if (tmp == NULL)
		return NULL;
	else
		return tmp->point;
}

struct point* rb_delete(struct rb_tree* tree, struct point* point)
{
	struct rb_node *tmp1, *tmp2, *tmp3;
	tmp1 = rb_node_search(tree,point);
	
	if (tmp1 == NULL)
		return NULL;
	
	tmp2 = tmp1;
	color tmp2_original_color = tmp2->color;

	if (tmp1->left == &sentinel) {
		tmp3 = tmp1->right;
		rb_transplant(tree,tmp1,tmp1->right);
	} else if(tmp1->right == &sentinel) {
		tmp3 = tmp1->left;
		rb_transplant(tree,tmp1,tmp1->left);
	} else {
		tmp2 = rb_min_node(tmp1->right);
		tmp2_original_color = tmp2->color;
		tmp3 = tmp2->right;

		if (tmp2->parent == tmp1) {
			tmp3->parent = tmp2;
		} else {
			rb_transplant(tree,tmp2,tmp2->right);
			tmp2->right = tmp1->right;
			tmp2->right->parent = tmp2;
		}

		rb_transplant(tree,tmp1,tmp2);
		tmp2->left = tmp1->left;
		tmp2->left->parent = tmp2;
		tmp2->color = tmp1->color;
	}

	if (tmp2_original_color == BLACK)
		rb_delete_fixup(tree,tmp3);
 	
	return point;
}




struct point* rb_min(struct rb_tree* tree)
{
	if (empty_rb_tree(tree))
		return NULL;

	struct rb_node* tmp;
	tmp = rb_min_node(tree->root);

	if (tmp != &sentinel)
		return tmp->point;
	else
		return NULL;
}



struct point* rb_max(struct rb_tree* tree)
{
	if (empty_rb_tree(tree))
		return NULL;

	struct rb_node* tmp;
	tmp = rb_max_node(tree->root);

	if (tmp != &sentinel)
		return tmp->point;
	else
		return NULL;
}
