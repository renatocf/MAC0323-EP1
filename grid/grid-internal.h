#ifndef H_GRID_INTERNAL_DEFINED
#define H_GRID_INTERNAL_DEFINED

#include "grid.h"

/* Definição de struct grid_p */
typedef struct grid_p *Link;
struct grid_p {
    point p;
    Link next;
};

/* Definição de Grid: matriz de links para struct grud_p */
struct grid {
    Link **g;
    int n_squares;
};

/* Funções de uso interno */
static void grid_insert(Grid grid, point p, float max);

#endif
