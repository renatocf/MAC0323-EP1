#ifndef H_PQUEUE_DEFINED
#define H_PQUEUE_DEFINED

/* Bibliotecas */
#include "ipqueue-item.h"

/* Handler para priority queue */
typedef struct ipQueue *IPQueue;

/* Funções para o cliente */
IPQ_Item ipq_get       (IPQueue, int);
IPQueue  ipq_init      (int);
int      ipq_size      (IPQueue);
void     ipq_sort      (IPQueue, int);
int      ipq_empty     (IPQueue);
void     ipq_insert    (IPQueue, IPQ_Item);
int      ipq_remove    (IPQueue);
void     ipq_replace   (IPQueue, IPQ_Item);
void     ipq_construct (IPQueue, int);
int      ipq_nelements (IPQueue);

#endif
