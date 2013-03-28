#ifndef H_PQUEUE_DEFINED
#define H_PQUEUE_DEFINED

/* Bibliotecas */
#include "pqueue-item.h"

/* Handler para priority queue */
typedef struct pQueue *PQueue;

/* Funções para o cliente */
PQueue pqinit      (int);
void   pqsort      (PQueue, int);
int    pqempty     (PQueue);
void   pqinsert    (PQueue, Item);
Item   pqremove    (PQueue);
void   pqreplace   (PQueue, Item);
void   pqconstruct (PQueue, int);

#endif
