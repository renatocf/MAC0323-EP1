#include<stdio.h>
#include "pqueue-internal.h"
#include "pltree.h"

int main(int argc, char **argv)
{
    PQueue teste;
    PLTree tree;
    int i, j;
    teste = pqinit(10);
    tree = pltree_init(teste->q);
    teste->q[0] = -1;
    
    for(i = 1; i-2 <= teste->size; i++)
    {
        pqinsert(teste, i);
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
    
    find_init(tree, teste->size);
    printf("dad: ");
    for(j = 0; j < teste->size; j++)
        printf("%d ", tree->dad[j]);
    printf("\n");
    
    union_find(tree, 1, 2, JOIN);
    printf("dad: ");
    for(j = 0; j < teste->size; j++)
        printf("%d ", tree->dad[j]);
    printf("\n");
    
    union_find(tree, 5, 7, JOIN);
    printf("dad: ");
    for(j = 0; j < teste->size; j++)
        printf("%d ", tree->dad[j]);
    printf("\n");
    
    if(union_find(tree, 2, 7, KEEP))
        printf("%d and %d are NOT from the same tree:\n", 2, 7);
    else 
        printf("%d and %d ARE from the same tree:\n", 2, 7);
    printf("dad: ");
    for(j = 0; j < teste->size; j++)
        printf("%d ", tree->dad[j]);
    printf("\n");
    
    union_find(tree, 2, 7, JOIN);
    printf("dad: ");
    for(j = 0; j < teste->size; j++)
        printf("%d ", tree->dad[j]);
    printf("\n");
    
    if(union_find(tree, 2, 7, KEEP))
        printf("%d and %d are NOT from the same tree:\n", 2, 7);
    else 
        printf("%d and %d ARE from the same tree:\n", 2, 7);
    printf("dad: ");
    for(j = 0; j < teste->size; j++)
        printf("%d ", tree->dad[j]);
    printf("\n");
    /* while(!pqempty(teste))  */
    /* { */
    /*     pqremove(teste); */
    /*     for(j = 0; j <= teste->last; j++) */
    /*         printf("%d ", teste->q[j]); */
    /*     printf("\n"); */
    /* } */
    
    return 0;
}
