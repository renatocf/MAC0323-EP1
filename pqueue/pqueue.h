#ifndef H_PQUEUE_DEFINED
#define H_PQUEUE_DEFINED

#include "Item2.h"

typedef struct pQueue *PQueue;

PQueue pqinit      (int);
void   pqsort      (PQueue, int);
int    pqempty     (PQueue);
void   pqinsert    (PQueue, Item);
Item   pqremove    (PQueue);
void   pqreplace   (PQueue, Item);
void   pqconstruct (PQueue, int);

#endif
