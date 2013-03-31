#ifndef H_GRID_DEFINED
#define H_GRID_DEFINED

/* Bibliotecas */
#include "Point.h"

/* Macros a serem usadas em grid_init */
#define NO_D 0
#define NO_M 0

/* Objetos */
typedef struct grid_p Grid_p;
typedef struct grid *Grid;

/* Célula cabeça padrão para todo grid */
extern Grid_p head;

/* Funções para manipulação do grid */
/* Consideremos:
 * - d:   distância máxima entre pontos. Se não houver, 
 *        o algoritmo pode calculá-la com base em M;
 * - max: tamanho da maior aresta do retângulo sobre
 *        o qual se usará o 'grid';
 * - N:   número de pontos total a ser processado;
 * - M:   número de pontos desejado para cada quadrado 
 *        do grid. Se não houver, pode ser estimado com 
 *        base em 'd'.
 */

Grid    grid_init          (float d, float max, int N, int M);
point   get_point          (Grid_p *t);
void    grid_construct     (Grid, point *, int N, float max);
Grid_p *get_grid_square    (Grid, int i, int j);
int     get_grid_n_squares (Grid);

#endif
