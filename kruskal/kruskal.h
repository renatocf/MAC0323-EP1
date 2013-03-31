#ifndef H_KRUSKAL_DEFINED
#define H_KRUSKAL_DEFINED

/* Bibliotecas */
#include "pltree-item.h"
#include "edge-item.h"

/* Definição de lista de arestas de um grafo */
typedef struct krList *KRlist;

/* Algoritmo de Krustal */
void kruskal(KRlist, int V, int E, void (*edgefound)(KRlist,int));

/* Funções para manipulação da lista */
KRlist  krlist_init        (PL_Item vertices, int E);
float   krlist_get_w       (KRlist, int);
E_Item *krlist_get_v1      (KRlist, int);
E_Item *krlist_get_v2      (KRlist, int);
void    krlist_insert_edge (KRlist, E_Item *, E_Item *, float);

#endif
