#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

void swap(queue_node_t n1, queue_node_t n2)
{
    int temp = n1.value;
    n1.value = n2.value;
    n2.value = temp;
}

int queue_init(queue_t *q)
{
    q->size = 0;
    q->head = q->tail = NULL;
  
    return 0;
}

int queue_delete(queue_t *q)
{

  int i;
  
    while (!queue_remove(q, &i))
      ;
  
    return 0;
}

int queue_add(queue_t *q, int v)
{
    if (q->head) 
    { 
        /**
         * If the queue is not empty create a new queue node
         * then swap the data until the data is in the right position
         */

        queue_node_t *toAdd = malloc(sizeof (*queue_node_t));
        
        if (toAdd == NULL) 
        {
          fprintf(stderr, "Out of memory.\n");
          return 1;
        }
        
        toAdd->value = v;
        queue_node_t cursor = q->head;

        while(cursor.next != NULL)
        {
            if(cursor.next.value < toAdd->value || cursor.next == q->tail)
            {
                cursor.next = toAdd;
            }
        }

        q->tail = q->tail->next;
        q->tail->value = v;
        q->tail->next = NULL;
        q->size++;

        while()
        {

        }

        return 0;
    }
    else
    {
        if (!(q->tail = q->head = malloc(sizeof (*q->tail)))) {
            fprintf(stderr, "Out of memory.\n");
      
            return 1;
          }
          q->tail->value = v;
          q->tail->next = NULL;
          q->size++;
      
          return 0;
    }

    return 0;
}

int queue_remove(queue_t *q, int *v)
{

}

int queue_peek(queue_t *q, int *v)
{
    if (q->size) {
        *v = q->head->value;
    
        return 0;
      }
    
      return 1;
}

int queue_size(queue_t *q)
{
    return q->size;
}
