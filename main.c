#include "binary_search_tree.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    BST *bst = bst_create();
    
    bst_insert(bst, element_create(10), ITERATIVE);
    bst_insert(bst, element_create(5), ITERATIVE);
    bst_insert(bst, element_create(15), ITERATIVE);
    bst_insert(bst, element_create(2), ITERATIVE);
    bst_insert(bst, element_create(1), ITERATIVE);
    bst_insert(bst, element_create(3), ITERATIVE);
    bst_insert(bst, element_create(7), ITERATIVE);
    bst_insert(bst, element_create(12), ITERATIVE);
    bst_insert(bst, element_create(20), ITERATIVE);

    
    printf("DEBUG\n");
    bst_print(bst, PRE_ORDER);
    bst_print(bst, IN_ORDER);
    bst_print(bst, POST_ORDER);

    printf("Deleting\n");
    bst_delete(bst, 5);
    bst_print(bst, PRE_ORDER);
    
    bst_delete(bst, 3);
    bst_print(bst, PRE_ORDER);
    
    bst_delete(bst, 10);
    bst_print(bst, PRE_ORDER);

    bst_destroy(&bst);    
    return 0;
}