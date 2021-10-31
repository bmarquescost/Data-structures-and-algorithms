#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

struct _node {
    NODE *next;
    ELEMENT *element;
};

struct _queue {
    NODE *start;
    NODE *end;
    int num_nodes;
};

NODE *_node_create(ELEMENT *e) {
    NODE *new_node = malloc(1 * sizeof(NODE));
    new_node->element = e;
    new_node->next = NULL;

    return new_node;
}

QUEUE *queue_create(void) {
    QUEUE *new_queue = malloc(1 * sizeof(QUEUE));
    new_queue->num_nodes = 0;
    new_queue->start = NULL;
    new_queue->end = NULL;

    return new_queue;
}


void queue_delete(QUEUE **q) {
    if(q == NULL) {
        printf("Deleting non existing queue.\n");
        return;
    }

    NODE *deleted_node = (*q)->start;

    while(deleted_node != NULL) {
        (*q)->start = deleted_node->next;
        element_delete(&deleted_node->element);
        deleted_node->next = NULL;
        free(deleted_node);

        deleted_node = (*q)->start;
    }
    
    free(*q);
}

void queue_enqueue(QUEUE *q, ELEMENT *e) {
    if(q == NULL || e == NULL) return;

    NODE *node = _node_create(e);

    if (q->end == NULL && q->start == NULL) {
        q->start = node;
    } else {
        q->end->next = node;
    }

    q-> end = node;

    ++(q->num_nodes);
}

ELEMENT *queue_dequeue(QUEUE *q) {
    if(q == NULL) return NULL;

    NODE *dequeud_node = q->start;
    q->start = dequeud_node->next;

    --(q->num_nodes);

    ELEMENT *dequeud_element = dequeud_node->element;

    dequeud_node->next = NULL;
    free(dequeud_node);
    dequeud_node = NULL;

    return dequeud_element;
}

void queue_print(QUEUE *q) {
    if(q == NULL) {
        printf("[]\n");
        return;
    }

    NODE *current_node = q->start;
    printf("[");
    while(current_node != NULL) {
        printf("%d", current_node->element->value);
        current_node = current_node->next;
        if(current_node != NULL) printf(", ");
    }

    printf("]\n");
}
