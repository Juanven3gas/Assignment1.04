#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

typedef struct node{
    int index;
    int priority;
    char *data;
} node_t;

typedef struct heap{
    node_t *nodes;
    int len;
    int size;
} heap_t;

void push (heap_t *h, int priority, char *data);
char *pop (heap_t *h);

#endif