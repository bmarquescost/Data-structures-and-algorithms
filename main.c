#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    STACK *new_stack = stack_create();
    
    for(int i = 0; i < 10; ++i) 
        stack_push(new_stack, element_create(i));
    stack_print(new_stack);

    printf("Deleting\n");
    free(stack_pop(new_stack));

    stack_print(new_stack);

    printf("Tentando inverter\n");
    stack_revert_recursively(new_stack);
    stack_print(new_stack);

    stack_delete(&new_stack);    
    return 0;
}