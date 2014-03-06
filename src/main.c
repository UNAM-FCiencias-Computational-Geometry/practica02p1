/**
 * Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
 *
 */

#include "algorithms/intersection.h"
#include "red_black_tree/rb_tree.h"
#include "double_linked_list/double_linked_list.h"


#include <stdlib.h>
#include <stdio.h>

int main(void)
{	
	
	struct double_linked_list *points_list, *segments_list;
	
	/** Creo una lista de puntos y de segmentos. */
	points_list = init_double_linked_list(POINT);
	segments_list = init_double_linked_list(HALF_EDGE);

	/** Destruyo la lista de puntos y de segments. */
	destroy_double_linked_list(points_list);
	destroy_double_linked_list(segments_list);
	
	struct rb_tree *tree_x, *tree_y;
	
	/** Creo un arbol rojo-negro que compara los puntos por la coordenada X
	 y otro arbol que compara los puntos por la coordenada Y*/
	tree_x = init_rb_tree(X);
	tree_y = init_rb_tree(Y);

	/** Destruyo ambos arboles. */
	destroy_rb_tree(tree_x);
	destroy_rb_tree(tree_y);

	return EXIT_SUCCESS;
}
