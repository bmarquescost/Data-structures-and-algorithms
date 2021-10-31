#ifndef _BST_H_
#define _BST_H_

#include "element.h"


#define ITERATIVE 1
#define RECURSIVE 2

enum orders {PRE_ORDER = 1, IN_ORDER, POST_ORDER};

typedef struct _node NODE;
typedef struct _bst BST;

BST *bst_create(void);
bool bst_insert(BST *, ELEMENT *, int);
bool bst_delete(BST *, int);
bool bst_search(BST *, int);
void bst_print(BST *, int);
void bst_destroy(BST **);

#endif