#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    LIST *new_list = list_create();
    
    for(int i = 0; i < 10; ++i) 
        list_push(new_list, element_create(i));

    list_print(new_list);
    list_invert(new_list);
    list_print(new_list);

    list_delete(&new_list);    

    return 0;
}