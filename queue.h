#ifndef QUEUE_H
#define QUEUE_H

typedef struct QNode {
    int data;       // Данные узла 
    struct QNode* next;     // Указатель на следующий 
} QNode;

typedef struct {
    QNode* front;       // Начало очереди 
    QNode* rear;        // Конец очереди 
} Queue;

void queue_init(Queue* q);
void queue_enqueue(Queue* q, int value);
int queue_dequeue(Queue* q);
int queue_peek(Queue* q);
bool queue_empty(Queue* q);
void queue_free(Queue* q);

#endif