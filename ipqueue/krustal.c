#include<stdlib.h>

/* Bibliotecas */
#include "edge.h"
#include "krustal.h"
#include "ipqueue.h"
#include "pltree.h"

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
void krustal(KRlist krlist, int V, int E, void (*edgefound) (int))
{   
    int r_pos; Edge removed; /* Aresta removida */
    int index_v1, index_v2;
    int i = 0; /* Auxiliar para número de arestas removidas */
    
    /* Inicializa parent link tree para vértices
     * e indirect priority queue para as arestas */
    find_init(krlist->vertices, V);
    ipq_construct(krlist->edges, E);
    
    /* Para a lista de arestas, busca pelas arestas de 
     * custo mínimo. Se encontrar V-1 arestas, têm uma
     * árvore de custo mínimo. Se o laço terminar, po-
     * rém, o grafo não é conexo. Quando uma aresta é 
     * encontrada, realiza a ação da função passada 
     * como parâmetro "edgefound". */
    while(!ipq_empty(krlist->edges))
    {
        r_pos = ipq_remove(krlist->edges);
        removed = ipq_get(krlist->edges, r_pos);
        PL_Item vertices = pltree_list(krlist->vertices);
        
        index_v1 = index(vertices, removed.v1);
        index_v2 = index(vertices, removed.v2);
        
        if(union_find(krlist->vertices, index_v1, index_v2, JOIN)) 
            { edgefound(r_pos); i++; }
        if(i == V-1) break;
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
    Edge new = { v1, v2, w };
    ipq_insert(krlist->edges, new);
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
