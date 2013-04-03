#include<stdio.h>
#include<stdlib.h>

/* Bibliotecas */
#include "Point.h"
#include "grid-internal.h"

/* Célula cabeça padrão para todos os grids */
Grid_p head;

Grid grid_init(float d, float max, int N, int M)
{
    int i, j; /* Auxiliares */
    Grid new;
    
    int n_squares; /* Lado dos quadrados do grid */
    
    if(d == NO_D) 
    {
        if(M == NO_M) return NULL;
        else 
           for(d = 1; d*d < (max*max*M)/N; d *= 2);
    }
    
    /* Número de quadrados de largura */
    n_squares = max/d; n_squares += 2;
    
    /* Alocação do grid */
    new = (Grid) malloc(sizeof(*new));
    new->n_squares = n_squares;
    
    /* Alocação dinâmica para a matriz que compõe o grid */
    new->g = (Link **) malloc(n_squares * sizeof(*new->g));
    if(new->g == NULL) printf("xii no início\n");
    for(i = 0; i < n_squares; i++)
        new->g[i] = (Link *) malloc(n_squares * sizeof(**new->g));
    
    /* Associa a cada célula da matric do grid a 'cabeça'
     * como sendo a célula seguinte. */
    for(i = 0; i < n_squares; i++)
        for(j = 0; j < n_squares; j++)
            new->g[i][j] = NULL;
    
    return new;
}

void grid_construct(Grid grid, point *points, int N, float max)
{
    int i = 0;
    for(i = 0; i <= N; i++) grid_insert(grid, points[i], max);
}

static void grid_insert(Grid grid, point p, float max)
{
    Grid_p *new; int G, X, Y; float d;
    new =  (Grid_p *) malloc(sizeof(*new));
    
    /* printf("grid_insert 1\n"); */
    d = max/grid->n_squares; 
    /* printf("d: %g\n", d); */
    
    G = 1/d; X = p.x*G+1; Y = p.y*G+1;
    
    /* Adiciona o ponto ao quadrado grid[p.x/d][p.y/d].
     * Usamos o auxiliar 'G' como forma de passar 'd'
     * de ponto flutuante para inteiro sem um cast. */
    new->p = p; new->next = grid->g[X][Y];
    grid->g[X][Y] = new;
}

int get_grid_n_squares(Grid grid)
{
    return grid->n_squares;
}

Grid_p *get_grid_square(Grid grid, int i, int j)
{
    if(i < 0 || i > grid->n_squares) return NULL;
    if(j < 0 || j > grid->n_squares) return NULL;
    return grid->g[i][j];
}

/* point get_point(Grid_p *t) */
/* { */
/*     point aux = t->p; */
/*     #<{(| if(t == NULL) return NULL; |)}># */
/*     return aux; */
/* } */
/*  */
/* float *get_point_x(Grid_p *t) */
/* { */
/*     if(t !=  */
/* } */
