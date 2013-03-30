#ifndef H_QUEUE_INCLUDED
#define H_QUEUE_INCLUDED

/* Bibliotecas */
#include "queue-item.h"

/* Define a estrutura de fila 'Queue' */
typedef struct queue *Queue;

/* Protótipos */
Queue  queueInit  (void);
Q_Item queueGet   (Queue);
void   queueFree  (Queue);
int    queueEmpty (Queue);
void   queuePut   (Queue, Q_Item);

#endif
