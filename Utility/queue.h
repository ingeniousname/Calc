#ifndef QUEUE_H_
#define QUEUE_H_

typedef struct Queue
{
    unsigned** q;
    int max, used;
}Queue;


int Qinit(Queue* queue);
int enqueue(Queue* queue, unsigned int* data);
unsigned* dequeue(Queue* queue);

void free_queue(Queue* queue);


#endif