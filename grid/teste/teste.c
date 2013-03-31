#include<stdio.h>
#include<stdlib.h>

#include "grid-internal.h"

int main()
{
    Grid teste;
    point p[] = { {0,0}, {1,1}, {0.5,0.5}};
    Grid_p *aux;
    int i, j;
    
    teste = grid_init(0.05, 1, 3, NO_M);
    grid_construct(teste, p, 3, 1);
   
    for(i = 0; i < teste->n_squares; i++)
        for(j = 0; j < teste->n_squares; j++) {
            printf("%d %d: ", i, j);
            /* aux = teste->g[i][j]; */
            /* if(aux == NULL) printf("problem!"); */
            for(aux = get_grid_square(teste, i, j); aux != NULL; aux = aux->next) 
            {
                printf("ERRO\n");
                if(aux == NULL) break;
                printf("entrou \n");
                printf("x:%f y:%f\n", /* 0.5, 0.5); */
                        aux->p.x, 
                        aux->p.y);
            }
            printf("\n");
        }
    
    printf("Hello, World!\n");
    
    return 0;
}
