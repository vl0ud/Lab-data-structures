#ifndef STACK_H
#define STACK_H

typedef struct {
    int* data;      // Указатель на массив
    int capacity;       // Максимальная вместимость
    int top;    // Вершина стека 
} Stack;

void stack_init(Stack* s, int capacity);
void stack_push(Stack* s, int value);
int stack_pop(Stack* s);
int stack_peek(Stack* s);
bool stack_empty(Stack* s);
void stack_free(Stack* s);

#endif