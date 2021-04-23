#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include "element.h"

typedef struct _node NODE;
typedef struct _list LIST;

LIST *list_create(void);
void list_delete(LIST **);
void list_push(LIST *, ELEMENT *);
void list_pop(LIST *, int);
ELEMENT *list_search(LIST *, int);
void list_print(LIST *); 
void list_invert(LIST *);

#endif