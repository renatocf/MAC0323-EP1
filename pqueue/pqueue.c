#include<stdlib.h>
#include<stdio.h>

/* Bibliotecas */
#include "pqueue-internal.h"

/*
////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------
                        FUNÇÕES DE USO EXTERNO   
-----------------------------------------------------------------------
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
PQueue pq_init(int N)
{
    PQueue new_pqueue;
    new_pqueue = (PQueue) malloc(sizeof(*new_pqueue));
    
    /* Inicializa nova priority queue com N+1 elementos,
     * tamanho 'N' e última posição preenchida como '0' */
    new_pqueue->last = 0; new_pqueue->size = N+1;
    new_pqueue->q = (PQ_Item *) malloc((N+1) * sizeof(*new_pqueue->q));
    
    return new_pqueue;
}

void pq_construct(PQueue pqueue, int last)
{
    build_maxheap(pqueue, last);
}

void pq_insert(PQueue pqueue, PQ_Item item)
{
    int item_position = pqueue->last + 1; 
    if(item_position <= pqueue->size)
    {
        pqueue->q[item_position] = item;
        pqueue->last = item_position;
        uphead(pqueue, item_position);
    }
}

void pq_replace(PQueue pqueue, PQ_Item item)
{
    pqueue->q[ROOT] = item;
    downheap(pqueue, ROOT, pqueue->last);
}

PQ_Item pq_remove(PQueue pqueue)
{
    PQ_Item removed = pqueue->q[ROOT];
    int last = pqueue->last;
    
    pqueue->q[ROOT] = pqueue->q[last];
    pqueue->last--;
    
    downheap(pqueue, ROOT, pqueue->last);
    return removed;
}

void pq_sort(PQueue pqueue, int last)
{
    heapsort(pqueue, last);
}

int pq_empty(PQueue pqueue)
{
    if(pqueue->last == 0) return 1;
    return 0;
}

int pq_size(PQueue pqueue)
{
    return pqueue->size;
}

int pq_nelements(PQueue pqueue)
{
    return pqueue->last;
}

PQ_Item pq_get(PQueue pqueue, int pos)
{
    return pqueue->q[pos];
}

/*
////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------
                        FUNÇÕES DE USO INTERNO   
-----------------------------------------------------------------------
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
static void uphead(PQueue pqueue, int k)
{
    PQ_Item aux = pqueue->q[k];
    int dad = k/2;
    
    while(le(pqueue->q[dad], aux) && dad != 0)
    {
        pqueue->q[k] = pqueue->q[dad];
        k = dad; dad = dad/2;
    }
    pqueue->q[k] = aux;
}

static void downheap(PQueue pqueue, int k, int last)
{
    int son = 2*k;
    PQ_Item aux = pqueue->q[k];

    /* Leva um elemento até sua posição no heap */
    while(son <= last)
    {
        if(son < last
        && le(pqueue->q[son], pqueue->q[son+1])) son++;
        if(le(pqueue->q[son], aux)) break;
        
        pqueue->q[k] = pqueue->q[son];
        k = son; son = 2*k;
    }
    pqueue->q[k] = aux;
}

static void build_maxheap(PQueue pqueue, int last)
{
    int aux; /* Contador auxiliar */
    for(aux = last/2; aux >= 1; aux--) 
        downheap(pqueue, aux, last);
}

static void heapsort(PQueue pqueue, int last)
{
    PQ_Item swp; /* AUxiliar para troca */

    /* Pré-processamento */
    build_maxheap(pqueue, last);
    
    /* Ordena o vetor */
    for(last = pqueue->last; last >= 2; last--)
    {
        swp = pqueue->q[ROOT];
        pqueue->q[ROOT] = pqueue->q[last];
        pqueue->q[last] = swp;
        
        downheap(pqueue, ROOT, last-1);
    }    
}
