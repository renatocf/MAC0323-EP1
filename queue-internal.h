#ifndef H_QUEUE_INTERNAL_INCLUDED
#define H_QUEUE_INTERNAL_INCLUDED
#include "Item.h"
#include "queue.h"

#define BUF_INIT_SIZE 50

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

/* Cria buffer para uso da biblioteca */
static Queue buffer;
static int buf_size = BUF_INIT_SIZE/2;

/* Funções de manipulação do buffer */
static void createBuffer();
static Link getBufferNode();
static void returnToBuffer(Link node);
static void resizeBuffer();
#endif
