#include "stack.h"
#include <iostream>
#include <stdexcept>
#include <string>

void stack_init(Stack* s, int capacity){
    s->data = new std::string[capacity];  // Выделяем массив строк
    s->capacity = capacity;
    s->top = -1;
}

void stack_push(Stack* s, const std::string& value){  // Принимаем строку
    if (s->top >= s->capacity - 1){
        int new_capacity = s->capacity * 2;
        std::string* new_data = new std::string[new_capacity];  // Новый массив строк
        for (int i = 0; i <= s->top; i++) new_data[i] = s->data[i];
        delete[] s->data;
        s->data = new_data;
        s->capacity = new_capacity;
    }
    s->data[++s->top] = value;  // Сохраняем строку
}

std::string stack_pop(Stack* s){  // Возвращаем строку
    if (s->top == -1) throw std::runtime_error("Stack is empty");
    return s->data[s->top--];
}

std::string stack_peek(Stack* s){  // Возвращаем строку
    if (s->top == -1) throw std::runtime_error("Stack is empty");
    return s->data[s->top];
}

bool stack_empty(Stack* s){ return s->top == -1; }

void stack_free(Stack* s){
    delete[] s->data;
    s->data = nullptr;
    s->capacity = s->top = 0;
}