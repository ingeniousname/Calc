#include "queue.h"
#include "stdlib.h"

int Qinit(Queue* queue)
{
    queue->q = malloc(sizeof(unsigned*));
    queue->max = 1;
    queue->used = 0;
}

int enqueue(Queue* queue, unsigned int* data)
{
    if(queue->used == queue->max)
    {
        unsigned** temp = realloc(queue->q, sizeof(char) * 2 * queue->max);
        if(temp == NULL) return 0;
        queue->q = temp;
        queue->max *= 2;
    }
    queue->q[queue->used] = data;
    queue->used++;    
    return 1;
}

unsigned* dequeue(Queue* queue)
{
    if(!queue->used) return NULL;
    queue->used--;
    unsigned* temp = queue->q[0];

    if(queue->used * 4 < queue->max)
    {
        queue->q = realloc(queue->q, sizeof(char) * (queue->max / 2 + 1));
        queue->max = queue->max / 2 + 1;
    }

    for(int i = 0; i < queue->used; i++)
    {
        queue->q[i] = queue->q[i + 1];
    }
    return temp;
}

void free_queue(Queue* queue)
{
    free(queue->q);
}