#ifndef H_EDGE_DEFINED
#define H_EDGE_DEFINED

#include "edge-item.h"

typedef struct edge Edge;
struct edge {
    E_Item *v1;
    E_Item *v2;
    float w;
};

#endif
