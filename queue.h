#ifndef H_QUEUE_INCLUDED
#define H_QUEUE_INCLUDED
#include "Item.h"

/* Define a estrutura de fila 'Queue' */
struct queue;
typedef struct queue *Queue;

/* Protótipos */
Queue queueInit();
int queueEmpty(Queue);
void queuePut(Queue, Item);
Item queueGet(Queue);
void queueFree();
#endif
