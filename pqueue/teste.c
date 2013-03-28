#include<stdio.h>
#include "pqueue-internal.h"

int main(int argc, char **argv)
{
    PQueue teste; int i, j;
    teste = pqinit(10);
    teste->q[0] = -1;
    
    for(i = 1; i-2 <= teste->size; i++)
    {
        pqinsert(teste, i);
        /* printf("%d\n", teste->last); */
        /* for(j = 0; j <= teste->last; j++) */
            /* printf("%d ", teste->q[j]); */
        /* printf("\n"); */
    }
    for(j = 0; j <= teste->last; j++)
        printf("%d ", teste->q[j]);
    printf("\n");
    
    pqreplace(teste, -2);
    for(j = 0; j <= teste->last; j++)
        printf("%d ", teste->q[j]);
    printf("\n");
    
    pqremove(teste);
    for(j = 0; j <= teste->last; j++)
        printf("%d ", teste->q[j]);
    printf("\n");
    
    pqsort(teste, teste->last);
    for(j = 0; j <= teste->last; j++)
        printf("%d ", teste->q[j]);
    printf("\n");
    
    while(!pqempty(teste)) 
    {
        pqremove(teste);
        for(j = 0; j <= teste->last; j++)
            printf("%d ", teste->q[j]);
        printf("\n");
    }
    
    return 0;
}
