#include<stdio.h>
#include "pqueue.h"

int main(int argc, char **argv)
{
    PQueue teste;
    int i, j;
    teste = pq_init(10);
    
    for(i = 1; i-2 <= pq_size(teste); i++)
        pq_insert(teste, i);
    for(j = 0; j <= pq_nelements(teste); j++)
        printf("%d ", pq_get(teste, j));
    printf("\n");
    
    pq_replace(teste, -2);
    for(j = 0; j <= pq_nelements(teste); j++)
        printf("%d ", pq_get(teste, j));
    printf("\n");
    
    pq_remove(teste);
    for(j = 0; j <= pq_nelements(teste); j++)
        printf("%d ", pq_get(teste, j));
    printf("\n");
    
    pq_sort(teste, pq_nelements(teste));
    for(j = 0; j <= pq_nelements(teste); j++)
        printf("%d ", pq_get(teste, j));
    printf("\n");
    
    while(!pq_empty(teste)) 
    {
        pq_remove(teste);
        for(j = 0; j <= pq_nelements(teste); j++)
            printf("%d ", pq_get(teste, j));
        printf("\n");
    }
    
    return 0;
}
