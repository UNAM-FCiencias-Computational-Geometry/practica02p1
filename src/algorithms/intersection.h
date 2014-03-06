/**
 * Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
 *
 * Description:
 * Contiene todas las funciones auxiliares que se implementan para 
 * procesar la interseccion de segmentos.
 */

#ifndef INTERSECTION_H_
#define INTERSECTION_H_

#include "double_linked_list/double_linked_list.h"

/**
 * Recibe una lista de segmentos (half_edges), y regresa una lista de puntos 
 * que representa al conjunto de intersecciones de los segmentos dados.
 * Cada punto hace referencia a los segmentos de los cuales pertenece el punto.
 */
struct double_linked_list* find_intersections(struct double_linked_list* 
											  half_edges);

#endif
