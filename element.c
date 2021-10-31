#include "element.h"
#include <stdlib.h>
#include <stdio.h>

ELEMENT *element_create(int value) {
    ELEMENT *new_element = malloc(sizeof(ELEMENT));
    new_element->value = value;
    return new_element;
}

int element_get_value(ELEMENT *e) {
    if (e == NULL) return ERROR;
    return e->value;
}

void element_delete(ELEMENT **e) {
    if(e == NULL) 
        return;
    free(*e);
}