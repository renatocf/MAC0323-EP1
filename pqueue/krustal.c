#include "pqueue.h"
#include "pltree.h"

struct edge {
    KR_Item *v1;
    KR_Item *v2;
    float w;
};

void krustal(KRlist edges)
{   
    /* PLTree edg = find_init(edges); */
    /* pqconstruct */
}

KRlist krlist_init(int N)
{
    PQueue edges; PLtree e;
    edges = pqinit(N);
    
    e = pltree_init(edges);
    
    return e;
}


float edge_weight(KR_list e, Edge edge) 
{
    return e->*plt[N]->w; 
}
