#ifndef STACK_H
#define STACK_H

#include <string>  // Добавлен для использования строк

typedef struct {
    std::string* data;      // Указатель на массив строк
    int capacity;       // Максимальная вместимость
    int top;    // Вершина стека 
} Stack;

void stack_init(Stack* s, int capacity);
void stack_push(Stack* s, const std::string& value);  
std::string stack_pop(Stack* s);  
std::string stack_peek(Stack* s);  
bool stack_empty(Stack* s);
void stack_free(Stack* s);

#endif