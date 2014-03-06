/**
 * Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
 *
 */

#include "types/types.h"

#include <stdio.h>
#include <stdlib.h>

struct half_edge* get_half_edge(struct point* point)
{
	if (point == NULL)
		return NULL;

	return (struct half_edge*)point->half_edge;
	
}

struct half_edge* cast_half_edge(void* half_edge)
{
	return (struct half_edge*)half_edge;
}

struct point* cast_point(void* point)
{
	return (struct point*)point;
}
