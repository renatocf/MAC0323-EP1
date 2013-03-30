#include<stdlib.h>
#include<stdio.h>

/* Bibliotecas */
#include "ipqueue-internal.h"

/*
////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------
                        FUNÇÕES DE USO EXTERNO   
-----------------------------------------------------------------------
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
IPQueue ipq_init(int N)
{
    IPQueue new_ipqueue;
    new_ipqueue = (IPQueue) malloc(sizeof(*new_ipqueue));
    
    /* Inicializa nova priority queue com N+1 elementos,
     * tamanho 'N' e última posição preenchida como '0' */
    new_ipqueue->last = 0; new_ipqueue->size = N+1;
    new_ipqueue->a = (IPQ_Item *) malloc((N+1) * sizeof(*new_ipqueue->a));
    
    /* Inicializa vetores de posição */
    new_ipqueue->p = (int *) malloc((N+1) * sizeof(*new_ipqueue->p));
    new_ipqueue->q = (int *) malloc((N+1) * sizeof(*new_ipqueue->q));
    
    return new_ipqueue;
}

void ipq_construct(IPQueue ipqueue, int last)
{
    int k; /* Auxiliar para inicializar 'p' e 'q' */
    
    for(k = 1; k <= last; k++) { ipqueue->p[k] = k; ipqueue->q[k] = k; }
    build_maxheap(ipqueue, last);
}

void ipq_insert(IPQueue ipqueue, IPQ_Item item)
{
    int item_position = ipqueue->last + 1; 
    if(item_position <= ipqueue->size)
    {
        ipqueue->a[item_position] = item;
        ipqueue->last = item_position;
        uphead(ipqueue, item_position);
    }
}

void ipq_replace(IPQueue ipqueue, IPQ_Item item)
{
    int *p = ipqueue->p;
    ipqueue->a[p[ROOT]] = item;
    downheap(ipqueue, ROOT, ipqueue->last);
}

int ipq_remove(IPQueue ipqueue)
{
    int last = ipqueue->last;
    int *p = ipqueue->p;
    int removed = last;
    IPQ_Item aux;
    
    /* Troca último elemento de posição com o
     * ROOT do heap */
    aux = ipqueue->a[p[ROOT]];
    ipqueue->a[p[ROOT]] = ipqueue->a[last];
    ipqueue->a[last] = aux;
    
    ipqueue->last--;
    
    ipq_construct(ipqueue, last);
    /* downheap(ipqueue, ROOT, ipqueue->last); */

    return removed;
}

void ipq_sort(IPQueue ipqueue, int last)
{
    heapsort(ipqueue, last);
}

int ipq_empty(IPQueue ipqueue)
{
    if(ipqueue->last == 0) return 1;
    return 0;
}

int ipq_size(IPQueue ipqueue)
{
    return ipqueue->size;
}

int ipq_nelements(IPQueue ipqueue)
{
    return ipqueue->last;
}

IPQ_Item ipqget(IPQueue ipqueue, int pos)
{
    return ipqueue->a[pos];
}

/*
////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------
                        FUNÇÕES DE USO INTERNO   
-----------------------------------------------------------------------
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
static void uphead(IPQueue ipqueue, int k)
{
    /* IPQ_Item aux = ipqueue->a[k]; */
    int aux = ipqueue->p[k];
    int *p = ipqueue->p;
    int *q = ipqueue->q;
    int dad = k/2;
    
    while(le(ipqueue->a[p[dad]], ipqueue->a[p[aux]]) && dad != 0)
    {
        p[k] = p[dad]; q[p[k]] = k;
        k = dad; dad /= 2;
    }
    p[k] = aux; q[aux] = k;
}

static void downheap(IPQueue ipqueue, int k, int last)
{
    int son = 2*k; /* Auxiliar para posição 'filho' */
    int *p = ipqueue->p; /* Ponteiro para lista 'p' */
    int *q = ipqueue->q; /* Ponteiro para lista 'q' */
    int aux = ipqueue->p[k]; /* Pos. de 'k' no heap */
    
    /* Troca posição do elemento até a certa no vetor
     * de poisções correspondente ao heap (p) */
    while(son <= last)
    {
        /* a[p[numero]] equivale, de forma indireta, ao heap */
        if(son < last
        && le(ipqueue->a[p[son]], ipqueue->a[p[son+1]])) son++;
        if(le(ipqueue->a[p[son]], ipqueue->a[aux])) break;
        
        /* q[p[k]] == k e p[q[k]] == k sempre. Por isso é
         * necessário corrigir a cada mudança de posições */
        p[k] = p[son]; q[p[k]] = k; 
        k = son; son *= 2;
    }
    p[k] = aux; q[aux] = k;
}

static void build_maxheap(IPQueue ipqueue, int last)
{
    int aux; /* Contador auxiliar */
    for(aux = last/2; aux >= 1; aux--) 
        downheap(ipqueue, aux, last);
}

static void heapsort(IPQueue ipqueue, int last)
{
    int swp1, aux;       /* Auxiliares para troca   */
    int *p = ipqueue->p; /* Ponteiro para lista 'p' */
    int *q = ipqueue->q; /* Ponteiro para lista 'q' */

    /* Pré-processamento */
    build_maxheap(ipqueue, last);
    
    /* Ordena o vetor que representa o heap (q) */
    for(aux = last; last >= 2; last--)
    {
        swp1 = p[ROOT]; p[ROOT] = p[last]; p[last] = swp1;
        downheap(ipqueue, ROOT, last-1);
    }
    /* Organiza o vetor inverso (q) a partir do heap (p) */
    for(swp1 = 1; swp1 <= aux; swp1++) q[p[swp1]] = swp1;
}
