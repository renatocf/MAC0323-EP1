#ifndef H_PQUEUE_ITEM_DEFINED
#define H_PQUEUE_ITEM_DEFINED

/* 
 * O Item utilizado pela priority queue deve
 * ser algum tipo (struct ou variável) simples.
 *
 * Para o dado tipo, devemos definir uma fun-
 * ção 'le' (less or equal - menor ou igual) 
 * que permita mostrar a prioridade entre os
 * objetos. 
 */

#include "edge.h"

typedef Edge IPQ_Item;
#define le(X,Y) (((X).w) <= ((Y).w))

#endif
