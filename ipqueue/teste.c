#include<stdio.h>
#include "Point.h"
#include "krustal.h"
#include "pltree-internal.h"
#include "ipqueue-internal.h"

#define N_VERTICES 3
#define N_EDGES 3

float max_w = -1;
void edgefound(KRlist krlist, int pos)
{
    float pos_w = krlist_get_w(krlist, pos);
    if(pos_w > max_w) max_w = pos_w;
}

int main()
{
    KRlist teste; int i = 0;
    point pontos[N_VERTICES] = { {0,0}, {1,1}, {0.5,0.5} };
    
    teste = krlist_init(pontos, N_EDGES);
    
    krlist_insert_edge(teste, &pontos[0], &pontos[1], 1.4142);
    krlist_insert_edge(teste, &pontos[0], &pontos[2], 1.4142/2);
    krlist_insert_edge(teste, &pontos[1], &pontos[2], 1.4142/2);
    
    printf("Getting distances:\n");
    for(i = 1; i <= 3; i++)
        printf("%g\n", krlist_get_w(teste, i));
    
    krustal(teste, N_VERTICES, N_EDGES, edgefound);
    printf("connectivity: %g\n", max_w);
    
    return 0;
}
