#include<stdlib.h>
#include "Item.h"
#include "queue.h"

#define BUF_INIT_SIZE 50

/* Nódulos que compõem a fila */
typedef struct node *Link;
struct node {
    Item item;
    Link next;
};
typedef struct node Node;

/* Define o tipo 'Fila' (queue) */
struct queue {
    Link init;
    Link end;
};
typedef struct queue *Queue;

/* Cria um buffer para ser usado pela biblioteca */
static Queue buffer;
static int buf_size = BUF_INIT_SIZE;

static void createBuffer();
static Link getBufferNode();
static void returnToBuffer(Link node);
static void resizeBuffer();

Queue queueInit()
{
    Queue new_queue;
    
    /* Inicializa a nova fila */
    new_queue = (Queue) malloc(sizeof(*new_queue));
    new_queue->init = new_queue->end = NULL;
    
    /* Cria buffer, caso este não tenha sido inicializado */
    if(buffer == NULL) createBuffer();
    
    return new_queue;
}

int queueEmpty(Queue queue)
{
    if(queue->end == NULL) return 1;
    return 0;
}

void queuePut(Queue queue, Item item)
{
    Link new_node;
    
    /* Checa disponibilidade do buffer */
    if(queueEmpty(buffer)) resizeBuffer();
    
    /* Cria novo nódulo da fila */
    new_node = getBufferNode(); 
    new_node->item = item;
    
    /* Inclui o novo nódulo na fila */
    new_node->next = NULL;
    queue->init->next = new_node;
    queue->init = new_node;
}

Item queueGet(Queue queue)
{
    Item vestige;
    Link old_node;
    
    /* Tira o nódulo da fila */
    old_node = queue->end;
    queue->end = queue->end->next;
    
    /* Devolve o nódulo para o buffer */
    vestige = old_node->item;
    returnToBuffer(old_node);
    
    return vestige;
}

void queueFree(Queue queue)
{
    Link next_node;
    while(!queueEmpty(queue))
    {
        next_node = queue->end;
        queue->end = queue->end->next;
        returnToBuffer(next_node);
    } 
}

static void createBuffer()
{
    int i = 0;
    buffer = (Queue) malloc(sizeof(*buffer));
    
    /* Vetor de nódulos, com tamanho BUF_INIT_SIZE */
    buffer->end = (Node *) malloc(BUF_INIT_SIZE * sizeof(*buffer));
    
    /* Nódulos apontam sequencialmente de um para outro */
    for(i = 0; i < BUF_INIT_SIZE; i++)
        buffer->end[i].next = &buffer->end[i+1];
    
    /* Arruma sinal para o fim da fila */
    buffer->init = &buffer->end[BUF_INIT_SIZE];
    buffer->init->next = NULL;
}

static Link getBufferNode()
{
    Link queue_node;
    
    /* Tira o nódulo da fila */
    queue_node = buffer->end;
    buffer->end = buffer->end->next;
    
    return queue_node;
}

static void returnToBuffer(Link node)
{
    /* Desassocia nódulo da fila antiga */
    node->next = NULL;
    
    /* Devolve nódulo ao buffer */
    buffer->init->next = node;
    buffer->init = node;
}

static void resizeBuffer()
{
    int i;
    Queue new_buffer;
    new_buffer = (Queue) malloc(sizeof(*new_buffer));
    
    /* Dobra o tamanho do buffer */
    buf_size = 2*buf_size;
    new_buffer->end = 
        (Node *) malloc(buf_size * sizeof(*new_buffer));
    
    /* Nódulos apontam sequencialmente de um para outro */
    for(i = 0; i < buf_size; i++)
        new_buffer->end[i] = buffer->end[i+1];

    /* Adicionamos os novos nódulos ao início da fila */
    buffer->init = new_buffer->end;
    
    /* Arruma sinal para o fim da fila */
    buffer->init = &new_buffer->end[buf_size];
    buffer->init->next = NULL;
    
    /* Libera o ponteiro auxiliar 'new_buffer' */
    free(new_buffer); new_buffer = NULL;
}
