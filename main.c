#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    HASH *hm = hash_create();

    for (int i = 0; i < 50; ++i) {
        hash_insert(hm, i);
        hash_insert(hm, i * i);
    }

    hash_display(hm);

    printf("Removing 0: %d\n", hash_remove(hm, 0));
    printf("Removing 10: %d\n", hash_remove(hm, 10));
    printf("Removing 10000: %d\n", hash_remove(hm, 10000));
    printf("Removing 230: %d\n", hash_remove(hm, 230));
    printf("Removing 390: %d\n", hash_remove(hm, 390));
    printf("Removing 4: %d\n", hash_remove(hm, 4));
    printf("Removing 2: %d\n", hash_remove(hm, 2));

    hash_destroy(&hm);
    return 0;
}