/**
 * Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
 *
 * Description:
 * Contiene la estructura junto con sus funciones que hacen referencia hacia 
 * puntos en 2D.
 */

#ifndef TWOD_POINTS_H_
#define TWOD_POINTS_H_

#define LEFT 0
#define RIGHT 1

struct point {
	double x;
	double y;
	
	/**
	 * Si es un punto que ayuda a representar un segmentos, entonces
	 * el apuntador de intersecion es nulo y el apuntador de half_edge
	 * hace referencia al segmento que ayuda a representar.
	 * Si el punto representa la interseccion de segmentos, entonces
	 * half_edge y intersection son los segmentos que contiene al punto.
	 *
	 * NOTA: Sus apuntadores son void* por que crearia conflictos al
	 * momento de compilar.
	 */
	void* half_edge;
	void* intersection;
};

/** Inicializa un punto con coordenadas por defecto 0 */
struct point* init_point_empty(void);

/** Inicializa un punto con las coordenadas que se le pasan */
struct point* init_point(double x, double y);

/** Libera la memoria que guarda la punto */
void destroy_point(struct point* point);

/** Crea una copia del punto que se le pase */
struct point* create_copy_point(struct point* point);

/*
 * Calcula el siguiente determinante:
 *          | 1 a->x a->y |
 * det(O) = | 1 b->x b->y |
 *	        | 1 c->x c->y |
 *
 * Si det(O) < 0 => Vuelta a la derecha.
 * Si det(O) > 0 => Vuelta a la izquierda.
 */
int curve_orientation(struct point* a, struct point* b, struct point* c);

/** Verifica si dos puntos tienen las mismas coordinadas. */
int points_equals(struct point* a, struct point* b);
#endif
