#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "element.h"

typedef struct _node NODE;
typedef struct _queue QUEUE;

QUEUE *queue_create(void);
void queue_delete(QUEUE **);
void queue_enqueue(QUEUE *, ELEMENT *);
ELEMENT *queue_dequeue(QUEUE *);
void queue_print(QUEUE *);

#endif