#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#define bool int
#define TRUE 1
#define FALSE 0

#define ERROR -1337

typedef struct _element {
    int value;
} ELEMENT;

ELEMENT *element_create(int);
int element_get_value(ELEMENT *);
void element_delete(ELEMENT **);

#endif