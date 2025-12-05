#include "queue.h"
#include <iostream>
#include <stdexcept>
#include <string> 

void queue_init(Queue* q){
    q->front = q->rear = nullptr;
}

void queue_enqueue(Queue* q, const std::string& value){  // Принимаем строку
    QNode* newNode = new QNode{value, nullptr};  // Создаем узел со строкой
    if (!q->rear) q->front = q->rear = newNode;
    else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

std::string queue_dequeue(Queue* q){  // Возвращаем строку
    if (!q->front) throw std::runtime_error("Queue is empty");
    QNode* temp = q->front;
    std::string value = temp->data;  // Получаем строку
    q->front = q->front->next;
    if (!q->front) q->rear = nullptr;
    delete temp;
    return value;
}

std::string queue_peek(Queue* q){  // Возвращаем строку
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