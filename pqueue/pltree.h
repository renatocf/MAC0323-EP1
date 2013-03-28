#ifndef H_PLTREE_DEFINED
#define H_PLTREE_DEFINED

#include "pltree-item.h"

/* Parent link tree (PLT) */
typedef struct plTree *PLTree;
struct plTree {
    PL_Item plt;
    int *dad;
};

/* Macros */
#define JOIN 1
#define KEEP 0

/* Funções de manipulação das PLT */
PLTree pltree_init(PL_Item item);
void find_init(PLTree pltree, int N);
int union_find(PLTree pltree, int x, int y, int join);

#endif
