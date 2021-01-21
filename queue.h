#ifndef AIRPORT_SIMULATION_QUEUE_H
#define AIRPORT_SIMULATION_QUEUE_H

#define MAXQUEUE 3 /* small value for testing */

typedef struct plane {
    int id; /* identification number of airplane */
    int tm; /* time of arrival in queue */
} Plane;

typedef Plane QueueEntry;

typedef struct queue {
    int count;
    int front;
    int rear;
    QueueEntry entry [MAXQUEUE];
} Queue;

void Append(QueueEntry, Queue *);
void CreateQueue(Queue *);
void Serve(QueueEntry *, Queue *);
int QueueSize(Queue *);
int QueueEmpty(Queue *);
int QueueFull(Queue *);

#endif //AIRPORT_SIMULATION_QUEUE_H
