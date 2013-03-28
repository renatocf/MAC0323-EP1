#ifndef H_PQUEUE_INTERNAL_DEFINED
#define H_PQUEUE_INTERNAL_DEFINED

#include "Item2.h"
#include "pqueue.h"

/* Macros */
#define ROOT 1

struct pQueue {
    int last;
    int size;
    Item *q;
};

static void uphead(PQueue pqueue, int k);
static void downheap(PQueue pqueue, int k, int last);
static void build_maxheap(PQueue pqueue, int last);
static void heapsort(PQueue pqueue, int last);

#endif
