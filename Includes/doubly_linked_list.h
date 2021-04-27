#ifndef _DLL_H_
#define _DLL_H_

#include "element.h"

typedef struct _node NODE; 
typedef struct _dll DLL;

DLL *dll_create(void);
void dll_delete(DLL **);
void dll_push(DLL *, ELEMENT *);
void dll_pop(DLL *, int );
ELEMENT *dll_search(DLL *, int );
void dll_print(DLL *);

#endif