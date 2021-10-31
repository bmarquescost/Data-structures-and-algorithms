#include "hash.h"
#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>


struct _hash {
    LIST **hash_map;
    int size;
};

HASH *hash_create() {
    HASH *hm = malloc(1 * sizeof(HASH));
    hm->hash_map = calloc(MAX, sizeof(LIST *));

    return hm;
}

static int hash_code(int key) {
    return (key % MAX);
}

void hash_insert(HASH *hm, int key) { 
    int index = hash_code(key); 
    if (hm->hash_map[index] == NULL) { // empty list in index at hash table
        hm->hash_map[index] = list_create();
        
        list_push(hm->hash_map[index], element_create(key));
    } else { // there is one or more values at the hash idx
        if (list_search(hm->hash_map[index], key) == NULL) 
            list_push(hm->hash_map[index], element_create(key));
    }
    hm->size++;
}

bool hash_remove(HASH *hm, int key) {
    if (hm == NULL) return FALSE;

    int index = hash_code(key);
    return list_remove_key(hm->hash_map[index], key);
}

void hash_destroy(HASH **hm) {
    if (*hm == NULL) return;

    for (int i = 0; i < MAX; ++i) 
        list_delete(&(*hm)->hash_map[i]);
}

void hash_display(HASH *hm) {
    printf("Display Hash Map:\n");
    for (int i = 0; i < MAX; ++i) {
        printf("[Hash id: %d] ", i);
        list_print(hm->hash_map[i]);
    }
}