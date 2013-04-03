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
    n_squares = (int) (max/d + 0.5); n_squares += 2;
    printf("max/d: %g\n", (max/d));
    
    /* Alocação do grid */
    new = (Grid) malloc(sizeof(*new));
    new->n_squares = n_squares;
    printf("n_squares: %d\n", n_squares-2);
    
    /* Alocação dinâmica para a matriz que compõe o grid */
    new->g = (Link **) malloc(n_squares * sizeof(*new->g));
    if(new->g == NULL) printf("xii no início\n");
    for(i = 0; i < n_squares; i++)
        new->g[i] = (Link *) malloc(n_squares * sizeof(**new->g));
    
    /* Associa a cada célula da matrix do grid a 'cabeça'
     * como sendo a célula seguinte. */
    for(i = 0; i < n_squares; i++)
        for(j = 0; j < n_squares; j++)
            new->g[i][j] = NULL;
    
    return new;
}

void grid_construct(Grid grid, point *points, int N, float max)
{
    int i = 0;
    for(i = 0; i < N; i++) grid_insert(grid, points[i], max);
}

static void grid_insert(Grid grid, point p, float max)
{
    Grid_p *new; int G, X, Y; float d;
    new =  (Grid_p *) malloc(sizeof(*new));
    
    /* printf("insert point.x: %g, point.y:%g\n", p.x, p.y); */
    
    /* printf("grid_insert 1\n"); */
    d = max/(grid->n_squares - 0.5); 
    
    G = 1/d; X = p.x*G+1; Y = p.y*G+1;
    /* printf("G: %d X:%d Y:%d\n", G, X, Y); */
    
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
