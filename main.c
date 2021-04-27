#include "double_linked_list.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    DLL *new_list = dll_create();
    
    for(int i = 0; i < 10; ++i) 
        dll_push(new_list, element_create(i));

    dll_print(new_list);

    printf("Deleting\n");
    dll_pop(new_list, 4);

    dll_print(new_list);

    dll_delete(&new_list);    

    return 0;
}