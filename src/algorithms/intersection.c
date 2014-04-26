/**
 * Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
 *
 */

#include "algorithms/intersection.h"
#include "red_black_tree/rb_tree.h"
#include "red_black_tree/rb_tree.c"


#include <stdio.h>
#include <stdlib.h>


void build_required_stops(struct rb_tree* stops, struct double_linked_list* edges){
	struct half_edge* tmp_edge;
	struct point *edge_first, *edge_last;
	
	while(!empty_list(edges)){
		printf("tomando la arista del frente de la lista...\n");
		tmp_edge= (struct half_edge*) pick_front(edges);
		printf("Tomando el primer punto\n");
		edge_first=tmp_edge->first;
		printf("Tomando el segundo punto\n");
		edge_last=tmp_edge->last;
		
		printf ("El nodo inicial es: (%lf,%lf)\n", edge_first->x,edge_first->y);
		printf ("El nodo final es: (%lf,%lf)\n", edge_last->x,edge_last->y);
		rb_insert(stops,edge_first);
		rb_insert(stops,edge_last);
		
		pop_front(edges);
	}
}

int is_ending_point(struct point* p){
	
	struct half_edge* egde = p->half_edge;
	struct point* p1 = egde->last;
	double x1 = p->x;
	double x2 = p1->x;
	double y1 = p->y;
	double y2 = p1->y;
	return (x2 == x1) && (y2==y1);
}

void addIntersections(struct rb_tree *state_tree, struct point* current_point, 
struct rb_tree* intersections, struct rb_tree* stops, struct rb_node* intersection){
	
	struct point* checking_point,*intersect_point_1,  *intersect_point_2;
	struct half_edge* edge,*checking_edge, *checking_intersection;
	
	intersect_point_1=NULL;
	intersect_point_2=NULL;
	
	edge= current_point->half_edge;
	
	checking_point= intersection->point;
	checking_edge= checking_point->half_edge;
	
	
	//if(is_ending_point(current_point)){
	
		struct point* aux = edge->first;
		rb_delete(state_tree,aux);
		if(checking_edge == edge){
			//checking_point ->half_edge = checking_point->intersection;
			if(checking_point->half_edge == NULL){
				rb_delete(state_tree,checking_point);
				}
			}
		
		//}
		
		if(checking_point->intersection == edge){
			checking_point ->intersection = NULL;
			
		
		}
	if(edge != checking_edge)
		intersect_point_1= he_intersection(checking_edge,edge);
	
	//checking_intersection= checking_point->intersection;
		
	if (intersect_point_1 != NULL && intersect_point_1 != current_point && intersect_point_1 != checking_point){
		rb_insert(intersections, intersect_point_1);
		rb_insert(stops, intersect_point_1);
		
		printf("Intersection found: (%lf,%lf)\n",intersect_point_1->x,intersect_point_1->y);
		
	}
	//if(edge != checking_intersection)
		//checking_intersection= checking_point->intersection;

	if(checking_point ->intersection != NULL && edge != checking_point->intersection ){
		checking_intersection= checking_point->intersection;
		intersect_point_2= he_intersection(checking_intersection,edge);
		if (intersect_point_2 != NULL && intersect_point_2 != current_point && intersect_point_2 != checking_point){
			rb_insert(intersections, intersect_point_2);
			rb_insert(stops, intersect_point_2);
				
			printf("Intersection found: (%lf,%lf)\n",intersect_point_2->x,intersect_point_2->y);
				
		}
	}
	//intersect_point_2 = NULL;
	if(intersect_point_2 != NULL || intersect_point_1 != NULL){
		rb_delete(state_tree,checking_point);
		rb_delete(state_tree, current_point);
		rb_delete(stops,checking_point);
		rb_delete(stops, current_point);
	}
}


void update_intersections(struct rb_tree* state_tree, struct point* point,struct rb_tree* intersections,
struct rb_tree* stops ){
	struct rb_node *node, *prev, *next;
	struct half_edge *edge, *prev_edge,*next_edge;
	struct point *prev_point, *next_point, *intersect_point;
	
	rb_insert(state_tree, point);
	node= rb_node_search(state_tree, point);
	printf("El punto actual del estado es: (%lf,%lf)\n",node->point->x,node->point->y);
	
	prev= getPrev(node);
	if (prev != NULL)
		addIntersections(state_tree, point, intersections, stops, prev);
	
	
	next= getNext(node);
	if (next != NULL)
		addIntersections(state_tree, point, intersections, stops, next);
	
	printf("\n");
	
}

struct rb_tree* sweep(struct rb_tree* stops){
	struct rb_tree* state_tree = init_rb_tree(Y);
	struct rb_tree* intersections = init_rb_tree(X);
	
	struct point* current;
	while(!empty_rb_tree(stops)){
		current=rb_min(stops);
		update_intersections(state_tree,current,intersections,stops);
		
		rb_delete(stops,current);
		
	}
	destroy_rb_tree(state_tree);
	destroy_rb_tree(stops);
	return intersections;
	
}







struct double_linked_list* find_intersections(struct double_linked_list* half_edges)
{
	//Código bueno
	
		if(half_edges != NULL){
			struct double_linked_list* edges= create_copy_list(half_edges),* intersections;
			struct rb_tree* intersecciones;
			
				if(!empty_list(edges)){ //build sweep line, edge by edge
					struct rb_tree* sweep_line= init_rb_tree(X);
					build_required_stops(sweep_line, edges);
					printf("\n\n\n\n\n\n");
					
					intersecciones=sweep(sweep_line);
					//sweep(sweep_line);
					
					//Prueba de linea
					printf("Ya se hizo el barrido de linea\n");
					struct point *equis;
					struct rb_node *nodo;
					
					while(! empty_rb_tree(intersecciones)){
						nodo=rb_min_node(intersecciones);
						equis=nodo->point;
						printf("La intersección actual es: (%lf,%lf)\n", equis->x, equis->y);

						rb_delete(intersecciones,equis);
					}
					
				destroy_rb_tree(intersecciones);
				printf("Ya acabó\n");
				intersections=init_double_linked_list(POINT);
				return intersections;
			}
			intersections= init_double_linked_list(POINT);
			return intersections;
		}
		return NULL;
		
		
		//Código para probar
	/*
	if(half_edges!=NULL){
		if(!empty_list(half_edges)){
			struct rb_tree *prueba = init_rb_tree(X);
			struct point *actual = init_point(0,2);
			rb_insert(prueba,actual);
			actual= init_point(2,0);
			rb_insert(prueba,actual);
			actual= init_point(1,1);
			rb_insert(prueba,actual);
			actual= init_point(1,0);
			rb_insert(prueba,actual);
			actual= init_point(2,2);
			rb_insert(prueba,actual);
			actual= init_point(2,3);
			rb_insert(prueba,actual);
			actual= init_point(0,1);
			rb_insert(prueba,actual);
			struct point *equis,*prev,*next;
			struct rb_node *nodo,*anterior,*siguiente;
			
			while(!empty_rb_tree(prueba)){
				nodo=rb_min_node(prueba);
				equis=nodo->point;
				printf("El punto actual es: (%lf,%lf)\n", equis->x, equis->y);
				
				printf("Por conseguir el anterior\n");
				anterior= getPrev(nodo);
				
				printf("Por conseguir el siguiente\n");
				siguiente= getNext(nodo);
				
				rb_delete(prueba,equis);
				printf("\n");
				anterior=siguiente=NULL;
			}
			
			destroy_rb_tree(prueba);
			destroy_rb_node(nodo);
		}
		return init_double_linked_list(POINT);
	}
	return NULL;
	*/
	//Fin código para probar
	
}









