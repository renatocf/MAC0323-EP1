#include<stdio.h>
#include<stdlib.h>

/* Bibliotecas */
#include "edge.h"
#include "krustal.h"
#include "ipqueue-internal.h"
#include "pltree-internal.h"

/* Estrutura krList */
struct krList {
    PLTree vertices;
    IPQueue edges;
};

/* Função auxiliar para restagar índice de vetor: */
static int index(PL_Item vector, PL_Item element) 
    { return vector - element; }

/*
////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------
                        FUNÇÕES DE USO EXTERNO   
-----------------------------------------------------------------------
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
void krustal(KRlist krlist, int V, int E, void (*edgefound)(KRlist,int))
{   
    PL_Item vertices; int index_v1, index_v2;
    int r_pos; Edge removed; /* Aresta removida */
    int i = 0; /* Auxiliar para número de arestas removidas */
    int j;
    
    /* Inicializa parent link tree para vértices
     * e indirect priority queue para as arestas */
    printf("\nfind_init:\n");
    find_init(krlist->vertices, V);
    for(j = 0; j < V; j++)
        printf("%d: %g %g\n", j, krlist->vertices->plt[j].x, krlist->vertices->plt[j].y);
    printf("Dad vector: ");
    for(j = 0; j < V; j++)
        printf("%d ", krlist->vertices->dad[j]);
    printf("\n");
    
    printf("\nipq_construct:\n");
    ipq_construct(krlist->edges, E);
    for(j = 1; j <= E; j++)
        printf("%g ", krlist->edges->a[j].w);
    printf("\n");
    for(j = 1; j <= E; j++)
        printf("%d ", krlist->edges->p[j]);
    printf("\n");
    
    /* Ponteiro para lista de vértices */
    vertices = pltree_list(krlist->vertices);
    
    /* Para a lista de arestas, busca pelas arestas de 
     * custo mínimo. Se encontrar V-1 arestas, têm uma
     * árvore de custo mínimo. Se o laço terminar, po-
     * rém, o grafo não é conexo. Quando uma aresta é 
     * encontrada, realiza a ação da função passada 
     * como parâmetro "edgefound". */
    printf("iiiiiiiiiii: %d\n", i);
    while(!ipq_empty(krlist->edges))
    {
        r_pos = ipq_remove(krlist->edges);
        removed = ipq_get(krlist->edges, r_pos);
        
        index_v1 = index(vertices, removed.v1);
        index_v2 = index(vertices, removed.v2);
        
        if(union_find(krlist->vertices, index_v1, index_v2, JOIN)) 
            { edgefound(krlist, r_pos); i++; }
        printf("i:%d V:%d\n", i, V);
        
        /* Debug */
        printf("\nVertices:\n");
        for(j = 0; j < V; j++)
            printf("%d: %g %g\n", j, krlist->vertices->plt[j].x, krlist->vertices->plt[j].y);
        printf("Dad vector: ");
        for(j = 0; j < V; j++)
            printf("%d ", krlist->vertices->dad[j]);
        printf("\n");
        
        printf("\nEdges:\n");
        for(j = 1; j <= E; j++)
            printf("%g ", krlist->edges->a[j].w);
        printf("\n");
        for(j = 1; j <= E; j++)
            printf("%d ", krlist->edges->p[j]);
        printf("\n");
        /* Debug */
        
        if(i == V-1) { printf("BREAK\n"); break; }
    }
}

KRlist krlist_init(PL_Item vertices, int E)
{
    KRlist new = (KRlist) malloc(sizeof(*new));
    
    /* Inicializa lista de prioridades para os vértices: */
    new->vertices = pltree_init(vertices);
    
    /* Inicializa parent link tree para os vértices */
    new->edges = ipq_init(E);
    return new;
}

void krlist_insert_edge(KRlist krlist, E_Item *v1, E_Item *v2, float w)
    /* VERIFICAR SE ESTOUROU O MÁXIMO */
{
    Edge *new = (Edge *) malloc(sizeof(*new));
    new->v1 = v1; new->v2 = v2; new->w = w;
    
    ipq_insert(krlist->edges, *new);
    free(new); new = NULL;
}

float krlist_get_w(KRlist krlist, int pos)
{    
    return ipq_get(krlist->edges, pos).w;
}

E_Item *krlist_get_v1(KRlist krlist, int pos)
{    
    return ipq_get(krlist->edges, pos).v1;
}

E_Item *krlist_get_v2(KRlist krlist, int pos)
{    
    return ipq_get(krlist->edges, pos).v2;
}
