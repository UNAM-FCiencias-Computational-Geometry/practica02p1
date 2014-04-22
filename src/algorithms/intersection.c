/**
 * Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
 *
 */

#include "algorithms/intersection.h"

#include <stdio.h>
#include <stdlib.h>

struct double_linked_list* find_intersections(struct double_linked_list*
											  half_edges)
{
	struct double_linked_list* intersections;
	struct list_item *tmp1, *tmp2;
		
	tmp1 = tmp2 = half_edges->head;
	intersections = init_double_linked_list(POINT);
		
	while(tmp1 != NULL){
		while(tmp2 != NULL){
			if(he_intersection(tmp1->element, tmp2->element) != NULL){
				push_back(intersections, he_intersection(tmp1->element, tmp2->element));
				tmp2 = tmp2->right;
			}else{
				tmp2 = tmp2->right;
			}
		}
		tmp1 = tmp1->right;
		tmp2 = tmp1;
	}
	return intersections;
}
