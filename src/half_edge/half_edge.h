/**
 * Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
 *
 * Description:
 * Dado que un segmento no tiene direcion, le llamaremos half_edge
 * a los segmentos con direccion que se representan.
 * 
 */

#ifndef HALF_EDGE_H_
#define HALF_EDGE_H_

#include "points/2d_points.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

/**
 * Estructura basica para representar segmentos con direccion.
 * Tiene un punto incian first y un punto final last.
 */
struct half_edge {
	struct point* first;
	struct point* last;
};

/**
 * Inicializa los segmentos pasandole la direccion de los puntos que lo 
 * describen.
 */
struct half_edge* init_half_edge(struct point* first, struct point* last);

/** Destruye el segmento liberando su memoria. */
void destroy_half_edge(struct half_edge* half_edge);

/** Destruye el segmento liberando su memoria y la de los puntos que contiene. */
void destroy_half_edge_with_points(struct half_edge* half_edge);

/** Crea una copia del segmento y sus puntos. */
struct half_edge* copy_half_edge(struct half_edge* half_edge);

/** 
 * Calcula la intersecion de dos segmentos, si no existe regresa nulo, y si
 * existe regresa el punto que esta en la intersecion de los dos segmentos.
 */
struct point* he_intersection(struct half_edge* a, struct half_edge* b);
#endif
