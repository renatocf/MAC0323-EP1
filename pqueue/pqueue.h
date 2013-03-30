#ifndef H_PQUEUE_DEFINED
#define H_PQUEUE_DEFINED

/* Bibliotecas */
#include "pqueue-item.h"

/* Handler para priority queue */
typedef struct pQueue *PQueue;

/* Funções para o cliente */
PQ_Item pq_get       (PQueue, int);
PQueue  pq_init      (int);
int     pq_size      (PQueue);
void    pq_sort      (PQueue, int);
int     pq_empty     (PQueue);
void    pq_insert    (PQueue, PQ_Item);
PQ_Item pq_remove    (PQueue);
void    pq_replace   (PQueue, PQ_Item);
void    pq_construct (PQueue, int);
int     pq_nelements (PQueue);

#endif
