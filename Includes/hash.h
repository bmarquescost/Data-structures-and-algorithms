#ifndef _HASH_H_
#define _HASH_H_

#include "element.h"

#define MAX 101

typedef struct _hash HASH;

HASH *hash_create();
void hash_insert(HASH *, int); 
bool hash_remove(HASH *, int);
void hash_destroy(HASH **);
void hash_display(HASH *);

#endif