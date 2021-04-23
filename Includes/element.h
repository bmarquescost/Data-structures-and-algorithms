#ifndef _ELEMENT_H_
#define _ELEMENT_H_

typedef struct _element {
    int value;
} ELEMENT;

ELEMENT *element_create(int);
void element_delete(ELEMENT **);

#endif