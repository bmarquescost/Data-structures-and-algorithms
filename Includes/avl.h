#ifndef _AVL_H_
#define _AVL_H_

#include "element.h"

#define ITERATIVE 1
#define RECURSIVE 2

enum orders {PRE_ORDER = 1, IN_ORDER, POST_ORDER};

typedef struct _node NODE;
typedef struct _avl AVL;

AVL *avl_create(void);
void avl_insert(AVL *, ELEMENT *);
void avl_remove(AVL *, int);
bool avl_search(AVL *, int);
void avl_print(AVL *, int);
void avl_destroy(AVL **);

#endif