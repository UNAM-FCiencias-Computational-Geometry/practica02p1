/**
 * Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
 * 
 */


#include "points/2d_points.h"

#include <stdlib.h>
#include <stdio.h>

struct point* init_point_empty()
{
	struct point* point = (struct point*) malloc(sizeof(struct point));

	if (point == NULL) {
		printf("Ya no hay memoria disponible: init_double_linked_list()");
		exit(EXIT_FAILURE);
	}

	point->x = 0.0;
	point->y = 0.0;

	point->half_edge = point->intersection = NULL;

	return point;
}

struct point* init_point(double x, double y)
{
	struct point* point = (struct point*) malloc(sizeof(struct point));

	if (point == NULL) {
		printf("Ya no hay memoria disponible: init_double_linked_list()");
		exit(EXIT_FAILURE);
	}
	
	point->x = x;
	point->y = y;

	point->half_edge = point->intersection = NULL;

	return point;
}

struct point* create_copy_point(struct point* point)
{
	struct point* new_point = init_point(point->x,point->y);
	
	return new_point;
}
void destroy_point(struct point* point)
{
	if (point != NULL)
		free(point);
}

int curve_orientation(struct point* a, struct point* b, struct point* c)
{
	int det_o = (b->x - a->x)*(c->y - a->y) - (c->x - a->x)*(b->y - a->y);
	if (det_o < 0) {
		return RIGHT;
	} else if (det_o > 0) {
		return LEFT;
	} else {
		printf("Puntos en posicion general: ");
		printf("a = (%f,%f), b = (%f,%f), c = (%f,%f)\n",
			   a->x,a->y,b->x,b->y,c->x,c->y);
		exit(EXIT_FAILURE);
	}
}

int points_equals(struct point* a, struct point* b)
{
	return ((a->x == b->x) && (a->y == b->y));
}
