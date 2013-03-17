#include "Item.h"

/* Define a estrutura de fila 'Queue' */
typedef struct node *Link;
struct node {
    Item item;
    Link next;
};
typedef struct node Node;
struct queue {
    Link init;
    Link end;
};
typedef struct queue *Queue;

/* Protótipos */
Queue queueInit();
int queueEmpty(Queue);
void queuePut(Queue, Item);
Item queueGet(Queue);
void queueFree();
