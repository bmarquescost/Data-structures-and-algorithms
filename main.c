#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    AVL *avl = avl_create();
    
    avl_insert(avl, element_create(10));
    avl_insert(avl, element_create(5));
    avl_insert(avl, element_create(15));
    avl_insert(avl, element_create(2));
    avl_insert(avl, element_create(1));
    avl_insert(avl, element_create(3));
    avl_insert(avl, element_create(7));
    avl_insert(avl, element_create(12));
    avl_insert(avl, element_create(20));

    
    printf("DEBUG\n");
    avl_print(avl, PRE_ORDER);
    avl_print(avl, IN_ORDER);
    avl_print(avl, POST_ORDER);

    printf("Deleting\n");
    avl_remove(avl, 5);
    avl_print(avl, PRE_ORDER);
    
    avl_remove(avl, 3);
    avl_print(avl, PRE_ORDER);
    
    avl_remove(avl, 10);
    avl_print(avl, PRE_ORDER);

    avl_destroy(&avl);    
    return 0;
}