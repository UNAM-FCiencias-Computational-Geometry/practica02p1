/**
 * Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
 *
 * Description:
 * Contiene los tipos que puede representar una lista. Y funciones
 * para Ruby-Processing.
 */

#ifndef TYPES_H_
#define TYPES_H_

#define FALSE 0
#define TRUE 1

#include "half_edge/half_edge.h"

typedef enum {POINT = 1, HALF_EDGE} item_type;

struct half_edge* get_half_edge(struct point*);

struct half_edge* cast_half_edge(void* half_edge);
struct point* cast_point(void* point);

#endif
