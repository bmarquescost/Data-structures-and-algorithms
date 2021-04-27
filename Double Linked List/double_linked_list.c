#include "double_linked_list.h"
#include <stdio.h>
#include <stdlib.h>

struct _node {
    NODE *next;
    NODE *previous;
    ELEMENT *element;
};

struct _dll {
    NODE *head; 
    NODE *tail;
    int num_nodes;
};

NODE *_node_create(ELEMENT *e) {
    NODE *new_node = malloc(sizeof(NODE));
    new_node->element = e;
    new_node->next = NULL;
    new_node->previous = NULL;

    return new_node;
}

DLL *dll_create(void) {
    DLL *new_dll = malloc(sizeof(DLL));
    new_dll->head = NULL;
    new_dll->tail = NULL;
    new_dll->num_nodes = 0;

    return new_dll;
}

void dll_delete(DLL **dll) {
    if(dll == NULL) {
        printf("Deleting non existing dll.\n");
        return;
    }
    if(*dll == NULL) {
        free(*dll);
        return;
    }
    else {
        NODE *deleted_node = (*dll)->head;

        while(deleted_node != NULL) {
            (*dll)->head = deleted_node->next;
            element_delete(&deleted_node->element);
            deleted_node->next = NULL;
            free(deleted_node);

            deleted_node = (*dll)->head;
        }
        
        free(*dll);
    }
}

void dll_push(DLL *dll, ELEMENT *e) {
    if(dll == NULL || e == NULL) return;

    NODE *new_node = _node_create(e);

    if(dll->num_nodes == 0)
        dll->head = new_node;
    
    else {
        dll->tail->next = new_node;
        new_node->previous = dll->tail;
    }

    dll->tail = new_node;
    ++dll->num_nodes;
}

void dll_pop(DLL *dll, int index) {
    if(dll == NULL) return;

    NODE *current_node = dll->head;
    int current_index = 0;
    
    while(current_node != NULL) {
        if(index == current_index) {
            if(current_node->previous == NULL) // poping dll head
                dll->head = current_node->next;
            
            else 
                current_node->previous->next = current_node->next;
            
            if(current_node == dll->tail) // Deleting dll tail
                dll->tail = current_node->previous;
            
            element_delete(&current_node->element);
            free(current_node);
            --dll->num_nodes;
            
            return;
        }

        current_node = current_node->next;
        ++current_index;
    }
}

ELEMENT *dll_search(DLL *dll, int key) {
    if(dll == NULL) return NULL;

    NODE *current_node = dll->head;
    while(current_node != NULL) {
        if(current_node->element->value == key)
            break;
        current_node = current_node->next;
    }

    return current_node->element;
}

void dll_print(DLL *dll) {
    if(dll == NULL) {
        printf("[]\n");
        return;
    }

    NODE *current_node = dll->head;
    printf("[");
    while(current_node != NULL) {
        printf("%d", current_node->element->value);
        current_node = current_node->next;
        if(current_node != NULL) printf(", ");
    }
    printf("]\n");
}