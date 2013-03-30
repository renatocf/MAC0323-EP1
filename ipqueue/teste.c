#include<stdio.h>
#include "ipqueue-internal.h"
#include "pltree-internal.h"
#include "edge.h"

#define N_ELEMENTS 10

int main(int argc, char **argv)
{
    int i, j;
    IPQueue teste;
    PLTree arvore;
    teste = ipq_init(N_ELEMENTS);
    arvore = pltree_init(teste);
    
    for(i = 1; i < ipq_size(teste); i++)
        ipq_insert(teste, i);
    
        printf("initial a: ");
        for(j = 0; j < ipq_size(teste); j++)
            printf("%d ", teste->a[j]->w);
    printf("\n");
    
    printf("%d x %d\n", teste->last,ipq_nelements(teste));
    
    printf("construct p: ");
    ipq_construct(teste, ipq_nelements(teste));
    for(j = 0; j < ipq_size(teste); j++)
        printf("%d ", teste->p[j]->w);
    printf("\n");
    printf("construct q: ");
    for(j = 0; j < ipq_size(teste); j++)
        printf("%d ", teste->q[j]->w);
    printf("\n");
    
    printf("Replace test:\n");
    ipq_replace(teste, -2);
    printf("a: ");
    for(j = 0; j <= ipq_nelements(teste); j++)
        printf("%d ", teste->a[j]->w);
    printf("\n");
    printf("p: ");
    for(j = 0; j <= ipq_nelements(teste); j++)
        printf("%d ", teste->p[j]->w);
    printf("\n");
    printf("q: ");
    for(j = 0; j <= ipq_nelements(teste); j++)
        printf("%d ", teste->q[j]->w);
    printf("\n");
    
    printf("Remove test:\n");
    ipq_remove(teste);
    printf("a: ");
    for(j = 0; j <= ipq_nelements(teste); j++)
        printf("%d ", teste->a[j]->w);
    printf("\n");
    printf("p: ");
    for(j = 0; j <= ipq_nelements(teste); j++)
        printf("%d ", teste->p[j]->w);
    printf("\n");
    printf("q: ");
    for(j = 0; j <= ipq_nelements(teste); j++)
        printf("%d ", teste->q[j]->w);
    printf("\n");
    
    printf("Sort test:\n");
    printf("%d\n", ipq_nelements(teste));
    ipq_sort(teste, ipq_nelements(teste));
    printf("a: ");
    for(j = 0; j <= ipq_nelements(teste); j++)
        printf("%d ", teste->a[j]->w);
    printf("\n");
    printf("p: ");
    for(j = 0; j <= ipq_nelements(teste); j++)
        printf("%d ", teste->p[j]->w);
    printf("\n");
    printf("q: ");
    for(j = 0; j <= ipq_nelements(teste); j++)
        printf("%d ", teste->q[j]->w);
    printf("\n");
    
    printf("Tree test:\n");
    printf("d: ");
    find_init(arvore, teste->size);
    for(j = 0; j <= ipq_nelements(teste); j++)
        printf("%d ", arvore->dad[j]->w);
    printf("\n");
    
    printf("Union-Find test:\n");
    printf("JOIN (1,2), JOIN(6,8), JOIN(2,8), KEEP(2,8)\n");
    printf("d: ");
    union_find(arvore, 1, 2, JOIN);
    for(j = 0; j <= ipq_nelements(teste); j++)
        printf("%d ", arvore->dad[j]->w);
    printf("\n");
    
    printf("d: ");
    union_find(arvore, 6, 8, JOIN);
    for(j = 0; j <= ipq_nelements(teste); j++)
        printf("%d ", arvore->dad[j]->w);
    printf("\n");
    
    printf("d: ");
    union_find(arvore, 2, 8, JOIN);
    for(j = 0; j <= ipq_nelements(teste); j++)
        printf("%d ", arvore->dad[j]->w);
    printf("\n");
    
    printf("d: ");
    union_find(arvore, 2, 8, KEEP);
    for(j = 0; j <= ipq_nelements(teste); j++)
        printf("%d ", arvore->dad[j]->w);
    printf("\n");
    
    return 0;
}
