#include "stack.h"
#include <stdio.h>
#include <stdlib.h>


struct _node {
    NODE *previous;
    ELEMENT *element;
};

struct _stack {
    NODE *top;
    int num_nodes;
};

NODE *_node_create(ELEMENT *e) {
    NODE *new_node = malloc(sizeof(NODE));
    new_node->element = e;
    new_node->previous = NULL;

    return new_node;
}

STACK *stack_create(void) {
    STACK *new_stack = malloc(1*sizeof(STACK));
    new_stack->num_nodes = 0;
    new_stack->top = 0;

    return new_stack;
}

void stack_delete(STACK **s) {
    if(s == NULL) {
        printf("Deleting non existing s.\n");
        return;
    }

    NODE *deleted_node = (*s)->top;

    while(deleted_node != NULL) {
        (*s)->top = deleted_node->previous;
        element_delete(&deleted_node->element);
        deleted_node->previous = NULL;
        free(deleted_node);

        deleted_node = (*s)->top;
    }
    
    free(*s);
}


void stack_push(STACK *s, ELEMENT *e) {
    if(s == NULL || e == NULL) return;

    NODE *node = _node_create(e);

    node->previous = s->top;
    s->top = node;
    ++s->num_nodes;
}

ELEMENT *stack_pop(STACK *s) {
    if(s == NULL) return NULL;

    NODE *popped_node = s->top;
    s->top = popped_node->previous;
    --s->num_nodes;

    ELEMENT *popped_element = popped_node->element;

    popped_node->previous = NULL;
    free(popped_node);
    popped_node = NULL;

    return popped_element;
}

void _insert_node_at_bottom(STACK *s, ELEMENT *e) {
    if(s->num_nodes == 0) 
        stack_push(s, e);
    
    else {
        ELEMENT *previous_element = stack_pop(s);
        _insert_node_at_bottom(s, e);
        stack_push(s, previous_element);
    }
}

void _stack_revert_recursively(STACK *s) {
    if(s->num_nodes != 0) {
        ELEMENT *stack_top = stack_pop(s);
        _stack_revert_recursively(s);
        _insert_node_at_bottom(s, stack_top);
    }
}

void stack_revert_recursively(STACK *s) {
    if(s == NULL) return;
    _stack_revert_recursively(s);
}

void stack_print(STACK *s) {
    if(s == NULL) {
        printf("[]\n");
        return;
    }

    NODE *current_node = s->top;
    printf("[");
    while(current_node != NULL) {
        printf("%d", current_node->element->value);
        current_node = current_node->previous;
        if(current_node != NULL) printf(", ");
    }
    printf("]\n");
}