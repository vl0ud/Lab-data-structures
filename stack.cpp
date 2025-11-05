#include "stack.h"
#include <iostream>
#include <stdexcept>

void stack_init(Stack* s, int capacity){
    s->data = new int[capacity];
    s->capacity = capacity;
    s->top = -1;        // -1 Стек пуст
}

void stack_push(Stack* s, int value){
    if (s->top >= s->capacity - 1){     // На переполнение 
        int new_capacity = s->capacity * 2;     // X2 
        int* new_data = new int[new_capacity];  
        for (int i = 0; i <= s->top; i++) new_data[i] = s->data[i]; 
        delete[] s->data;   
        s->data = new_data; 
        s->capacity = new_capacity;
    }
    s->data[++s->top] = value;
}

int stack_pop(Stack* s){        // Извлечение верхнего элемента 
    if (s->top == -1) throw std::runtime_error("Stack is empty");
    return s->data[s->top--];
}

int stack_peek(Stack* s){       // Верхний элемент без извлечения 
    if (s->top == -1) throw std::runtime_error("Stack is empty");
    return s->data[s->top];
}

bool stack_empty(Stack* s){ return s->top == -1; }      // Проверка на пустоту 

void stack_free(Stack* s){
    delete[] s->data;
    s->data = nullptr;
    s->capacity = s->top = 0;
}