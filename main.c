#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    QUEUE *new_queue = queue_create();
    
    for(int i = 0; i < 10; ++i) 
        queue_enqueue(new_queue, element_create(i));
    
    printf("DEBUG\n");
    queue_print(new_queue);

    printf("Deleting\n");
    free(queue_dequeue(new_queue));
    queue_print(new_queue);

    for (int i = 0; i < 5; ++i) {
        free(queue_dequeue(new_queue));
        queue_print(new_queue);
    }

    queue_delete(&new_queue);    
    return 0;
}