#ifndef H_PQUEUE_DEFINED
#define H_PQUEUE_DEFINED

/* Bibliotecas */
#include "ipqueue-item.h"

/* Handler para priority queue */
typedef struct ipQueue *IPQueue;

/* Funções para o cliente */
IPQueue  ipqinit      (int);
int      ipqsize      (IPQueue);
void     ipqsort      (IPQueue, int);
int      ipqempty     (IPQueue);
void     ipqinsert    (IPQueue, IPQ_Item);
int      ipqremove    (IPQueue);
void     ipqreplace   (IPQueue, IPQ_Item);
void     ipqconstruct (IPQueue, int);
int      ipqnelements (IPQueue);

#endif
