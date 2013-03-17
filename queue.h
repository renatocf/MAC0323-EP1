#include "Item.h"

/* Define os nódulso da fila e os links para eles */
typedef struct node *Link;
typedef struct node {
    Item item;
    Link next;
} Node;

/* Define a estrutura de fila 'Queue' */
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
