#include "pqueue.h"
#include "pltree.h"

struct edge {
    KR_Item *v1;
    KR_Item *v2;
    float w;
};

void krustal(KRlist krlist, int V, int E)
{   
    PQueue edges = pltree_list(krlist);
    int i = 0, N = pqsize(edges);
    
    find_init(krlist, N);
    pqconstruct(edges);
    
    while(!pqempty(edges))
    {
        
    }
}

KRlist krlist_init(int N)
{
    PQueue edges; /* edges é uma pqueue de 
                   * struct edge (Edge) */
    KRlist new;   /* KRList é uma pltree 
                   * cuja lista é uma pqueue */
    
    edges = pqinit(N);
    new = pltree_init(edges);
    return new;
}

void krlist_insert(KRlist krlist, KR_Item *v1, KR_Item *v2, float w)
    /* VERIFICAR SE ESTOUROU O MÁXIMO */
{
    PQueue edges = pltree_list(krlist);
    Edge new = { v1, v2, w };
    
    pqinsert(edges, new);
}

/*Edge krlist_remove(KRlist krlist)
{
    PQueue edges = pltree_list(krlist);
    Edge deleted = pqremove(edges);
    
    return deleted;
}

int krlist_empty(KRlist krlist)
{
    PQueue edges = pltree_list(krlist);
    return pqempty(edges);
}*/
