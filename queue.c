#include "queue.h"
#include <stdio.h>

/* CreateQueue: create the queue.
    Pre: None.
    Post: The queue q has been initialized to be empty. */
void CreateQueue(Queue *q)
{
    q->count = 0;
    q->front = 0;
    q->rear = -1;
}

/* Append: append an entry to the queue.
    Pre: The queue q has been created and is not full.
    Post: The entry x has been stored in the queue as its last entry.
    Uses: QueueFull, Error. */
void Append(QueueEntry x, Queue *q) {
    if (QueueFull(q))
        printf("Cannot append an entry to a full queue.\n");
    else {
        q->count++;
        q->rear = (q->rear + 1) % MAXQUEUE;
        q->entry[q->rear] = x;
    }
}

/* Serve: remove the first entry in the queue.
    Pre: The queue q has been created and is not empty.
    Post: The first entry in the queue has been removed and returned as the value ofx.
    Uses: QueueEmpty, Error. */
void Serve(QueueEntry *x, Queue *q) {
    if (QueueEmpty(q))
        printf("Cannot serve from an empty queue.\n");
    else {
        q->count--;
        *x = q->entry[q->front];
        q->front = (q->front + 1) % MAXQUEUE;
    }
}

/* QueueSize: return the number of entries in the queue.
    Pre: The queue q has been created.
    Post: The function returns the number of entries in the queue q. */
int QueueSize(Queue *q) {
    return q->count;
}

/* QueueEmpty: returns non-zero if the queue is empty.
    Pre: The queue q has been created.
    Post: The function returns non-zero if the queue q is empty zero otherwise. */
int QueueEmpty(Queue *q) {
    return q->count <= 0;
}
/* QueueFull: returns non-zero if the queue is full.
Pre: The queue q has been created.
Post: The function returns non-zero if the queue is full, zero otherwise. */
int QueueFull(Queue *q) {
    return q->count >= MAXQUEUE;
}