#include "queue.h"
#include <iostream>
#include <stdexcept>

void queue_init(Queue* q){
    q->front = q->rear = nullptr;
}

void queue_enqueue(Queue* q, int value){
    QNode* newNode = new QNode{value, nullptr};
    if (!q->rear) q->front = q->rear = newNode;     // Пуста -> начало и конец одно и то же 
    else {
        q->rear->next = newNode;        // Старый последний --> на новый
        q->rear = newNode;
    }
}

int queue_dequeue(Queue* q){
    if (!q->front) throw std::runtime_error("Queue is empty");
    QNode* temp = q->front;     // Временное сохранение 1 узла в очереди 
    int value = temp->data;
    q->front = q->front->next;      // Сдвиг влево
    if (!q->front) q->rear = nullptr;
    delete temp;
    return value;
}

int queue_peek(Queue* q){
    if (!q->front) throw std::runtime_error("Queue is empty");
    return q->front->data;
}

bool queue_empty(Queue* q){ return q->front == nullptr; }

void queue_free(Queue* q){
    while (q->front){
        QNode* temp = q->front;
        q->front = q->front->next;
        delete temp;
    }
    q->rear = nullptr;
}