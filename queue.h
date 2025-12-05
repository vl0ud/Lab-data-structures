#ifndef QUEUE_H
#define QUEUE_H

#include <string>  // Добавлен для использования строк

typedef struct QNode {
    std::string data;       // Данные узла - строка
    struct QNode* next;     // Указатель на следующий 
} QNode;

typedef struct {
    QNode* front;       // Начало очереди 
    QNode* rear;        // Конец очереди 
} Queue;

void queue_init(Queue* q);
void queue_enqueue(Queue* q, const std::string& value); 
std::string queue_dequeue(Queue* q);  
std::string queue_peek(Queue* q);  
bool queue_empty(Queue* q);
void queue_free(Queue* q);

#endif