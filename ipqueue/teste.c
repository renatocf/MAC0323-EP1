#include<stdio.h>
#include "ipqueue-internal.h"

#define N_ELEMENTS 10

int main(int argc, char **argv)
{
    int i, j;
    IPQueue teste;
    teste = ipqinit(N_ELEMENTS);
    
    for(i = 1; i < ipqsize(teste); i++)
        ipqinsert(teste, i);
    
    printf("initial a: ");
    for(j = 0; j < ipqsize(teste); j++)
        printf("%d ", teste->a[j]);
    printf("\n");
    
    printf("%d x %d\n", teste->last,ipqnelements(teste));
    
    printf("construct p: ");
    ipqconstruct(teste, ipqnelements(teste));
    for(j = 0; j < ipqsize(teste); j++)
        printf("%d ", teste->p[j]);
    printf("\n");
    printf("construct q: ");
    for(j = 0; j < ipqsize(teste); j++)
        printf("%d ", teste->q[j]);
    printf("\n");
    
    printf("Replace test:\n");
    ipqreplace(teste, -2);
    printf("a: ");
    for(j = 0; j <= ipqnelements(teste); j++)
        printf("%d ", teste->a[j]);
    printf("\n");
    printf("p: ");
    for(j = 0; j <= ipqnelements(teste); j++)
        printf("%d ", teste->p[j]);
    printf("\n");
    printf("q: ");
    for(j = 0; j <= ipqnelements(teste); j++)
        printf("%d ", teste->q[j]);
    printf("\n");
    
    printf("Remove test:\n");
    ipqremove(teste);
    printf("a: ");
    for(j = 0; j <= ipqnelements(teste); j++)
        printf("%d ", teste->a[j]);
    printf("\n");
    printf("p: ");
    for(j = 0; j <= ipqnelements(teste); j++)
        printf("%d ", teste->p[j]);
    printf("\n");
    printf("q: ");
    for(j = 0; j <= ipqnelements(teste); j++)
        printf("%d ", teste->q[j]);
    printf("\n");
    
    printf("Sort test:\n");
    printf("%d\n", ipqnelements(teste));
    ipqsort(teste, ipqnelements(teste));
    printf("a: ");
    for(j = 0; j <= ipqnelements(teste); j++)
        printf("%d ", teste->a[j]);
    printf("\n");
    printf("p: ");
    for(j = 0; j <= ipqnelements(teste); j++)
        printf("%d ", teste->p[j]);
    printf("\n");
    printf("q: ");
    for(j = 0; j <= ipqnelements(teste); j++)
        printf("%d ", teste->q[j]);
    printf("\n");
    
    return 0;
}
