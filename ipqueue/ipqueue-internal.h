#ifndef H_IPQUEUE_INTERNAL_DEFINED
#define H_IPQUEUE_INTERNAL_DEFINED

/* Bibliotecas */
#include "ipqueue.h"

/* Macros */
#define ROOT 1

struct ipQueue {
    IPQ_Item *a; /* Vetor de itens */
    int last;    /* Última posição preenchia de 'a'   */
    int size;    /* Tamanho (na inicialização) de 'a' */
    int *p;      /* Dado um registro do heap, acha o
                  * elemento correspondente em 'a'    */
    int *q;      /* Dado um registro de 'a', acha a 
                  * posição do elemento no heap       */
};

/* Funções de uso interno */
static void uphead        (IPQueue ipqueue, int k);
static void downheap      (IPQueue ipqueue, int k, int last);
static void build_maxheap (IPQueue ipqueue, int last);
static void heapsort      (IPQueue ipqueue, int last);

#endif
