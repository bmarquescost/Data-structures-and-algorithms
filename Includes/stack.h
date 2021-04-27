#ifndef _STACK_H_
#define _STACK_H_

#include "element.h"

typedef struct _node NODE;
typedef struct _stack STACK;

STACK *stack_create(void);
void stack_delete(STACK **);
void stack_push(STACK *, ELEMENT *);
ELEMENT *stack_pop(STACK *);
void stack_revert_recursively(STACK *);
void stack_print(STACK *s);

#endif