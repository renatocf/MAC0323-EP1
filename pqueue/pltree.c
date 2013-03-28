#include<stdio.h>
#include<stdlib.h>

/* Bibliotecas */
#include "pltree.h"

/* Estrutura de uma Parent Link Tree */
/* struct plTree { */
/*     PL_Item plt; */
/*     int *dad; */
/* }; */

/*
////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------
                        FUNÇÕES DE USO EXTERNO   
-----------------------------------------------------------------------
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
PLTree pltree_init(PL_Item item)
{
    PLTree new;
    new = (PLTree) malloc(sizeof(*new));
    
    new->plt = item;
    return new;
}

void find_init(PLTree pltree, int N)
{
    int i = 0; /* Auxiliar para percorrer a pltree */
    
    pltree->dad = (int *) malloc(N * sizeof(*pltree->dad));
    for(i = 0; i < N; i++) pltree->dad[i] = 0;
}

int union_find(PLTree pltree, int x, int y, int join)
{
    int t, i = x, j = y;
    /* Percorre as "parent link trees" para encontrar
     * qual a raiz das árvores dos elementos 'x' e 'y' */
    while(pltree->dad[i] > 0) i = pltree->dad[i];
    while(pltree->dad[j] > 0) j = pltree->dad[j];
    
    /* Realiza uma compressão da árvore, fazendo com que
     * os ramos se conectem diretamente à raiz sem os ele-
     * mentos acima (aumenta a velocidade em buscas) */
    while(pltree->dad[x] > 0) 
        { t = x; x = pltree->dad[x]; pltree->dad[t] = i; }
    while(pltree->dad[y] > 0)
        { t = y; y = pltree->dad[y]; pltree->dad[t] = j; }
    
    /* Se a flag 'doit' estier setada, realiza a operação
     * de 'união' das árvores, deixando como raiz a árvore
     * com maior número de ramos. */
    if((join != 0) && (i != j))
    {
        if(pltree->dad[j] < pltree->dad[i])
        { 
            pltree->dad[j] += pltree->dad[i] - 1; 
            pltree->dad[i] = j; 
        }
        else
        { 
            pltree->dad[i] += pltree->dad[j] - 1; 
            pltree->dad[j] = i; 
        }
    }
    
    /* Retorna 1 se os elementos estiverem em árvores dife-
     * rentes e 0 no caso contrário. */
    return (i != j);
}
