#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>

struct _node {
    NODE *next;
    ELEMENT *element;    
};

struct _list {
    NODE *head; 
    NODE *tail;
    int n_nodes;  
};

NODE *_node_create(ELEMENT *e) {
    NODE *new_node = malloc(sizeof(NODE));
    new_node->element = e;
    new_node->next = NULL;

    return new_node;
}

LIST *list_create(void) {
    LIST *new_list = malloc(sizeof(LIST));
    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->n_nodes = 0;

    return new_list;
}

void list_delete(LIST **l) {
    if(l == NULL) {
        printf("Deleting non existing list.\n");
        return;
    }
    if(*l == NULL) {
        free(*l);
        return;
    }
    else {
        NODE *deleted_node = (*l)->head;

        while(deleted_node != NULL) {
            (*l)->head = deleted_node->next;
            element_delete(&deleted_node->element);
            deleted_node->next = NULL;
            free(deleted_node);

            deleted_node = (*l)->head;
        }
        
        free(*l);
    }
}

void list_push(LIST *l, ELEMENT *e) {
    if(l == NULL || e == NULL)
        return;

    NODE *new_node = _node_create(e);

    if(l->n_nodes == 0)
        l->head = new_node;
    else 
        l->tail->next = new_node;
    
    l->tail = new_node;
    ++l->n_nodes;
}

void list_pop(LIST *l, int index) {
    if(l == NULL) 
        return;
    
    NODE *previous_node = NULL;
    NODE *current_node = l->head;
    int current_index = 0;
    
    while(current_node != NULL) {
        if(index == current_index) {
            if(previous_node != NULL) 
                previous_node->next = current_node->next;
            
            else 
                l->head = current_node->next;

            if(current_node == l->tail) 
                l->tail = previous_node;
            
            element_delete(&current_node->element);
            free(current_node);
            --l->n_nodes;
            return;
        }

        previous_node = current_node;
        current_node = current_node->next;
    }
}

ELEMENT *list_search(LIST *l, int key) {
    if(l == NULL)
        return NULL;
    
    NODE *current_node = l->head;
    while(current_node != NULL) {
        if(current_node->element->value == key) 
            break;
        current_node = current_node->next;
    }

    return current_node->element;
}

void list_invert(LIST *l) {
    if(l == NULL) 
        return;
    
    NODE *first_node = l->head->next;
    NODE *middle_node = l->head;
    NODE *last_node = NULL;

    while(first_node != NULL) {
        last_node = middle_node;
        middle_node = first_node;
        first_node = first_node->next;
        middle_node->next = last_node;
    }
    l->head->next = NULL;
    l->tail = l->head;
    l->head = middle_node;
}

void list_print(LIST *l) {
    if(l == NULL) {
        printf("[]\n");
        return;
    }

    NODE *current_node = l->head;
    printf("[");
    while(current_node != NULL) {
        printf("%d", current_node->element->value);
        current_node = current_node->next;
        if(current_node != NULL) printf(", ");
    }
    printf("]\n");
}