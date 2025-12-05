#include "array.h"
#include <iostream>
#include <stdexcept>        // Либа для исключений
#include <string>          

void array_init(Array* arr, int capacity){
    arr->data = new std::string[capacity];  // Выделяем массив строк
    arr->size = 0;
    arr->capacity = capacity;
}

void array_add_back(Array* arr, const std::string& value){  // Принимаем строку
    if (arr->size >= arr->capacity){    // Условие на переизбыток
        int new_capacity = arr->capacity * 2;
        std::string* new_data = new std::string[new_capacity];  // Новый массив строк
        for (int i = 0; i < arr->size; i++) new_data[i] = arr->data[i];
        delete[] arr->data;
        arr->data = new_data;
        arr->capacity = new_capacity;
    }
    arr->data[arr->size++] = value;     // Добавление строки
}

void array_add_index(Array* arr, int index, const std::string& value){  // Принимаем строку
    if (index < 0 || index > arr->size) throw std::out_of_range("Index out of range");
    if (arr->size >= arr->capacity){
        int new_capacity = arr->capacity * 2;
        std::string* new_data = new std::string[new_capacity];
        for (int i = 0; i < arr->size; i++) new_data[i] = arr->data[i];
        delete[] arr->data;
        arr->data = new_data;
        arr->capacity = new_capacity;
    }
    for (int i = arr->size; i > index; i--) arr->data[i] = arr->data[i-1];
    arr->data[index] = value;       // Вставка строки
    arr->size++;
}

std::string array_get_index(Array* arr, int index){  // Возвращаем строку
    if (index < 0 || index >= arr->size) throw std::out_of_range("Index out of range");
    return arr->data[index];
}

void array_remove_index(Array* arr, int index){
    if (index < 0 || index >= arr->size) throw std::out_of_range("Index out of range");
    for (int i = index; i < arr->size - 1; i++) arr->data[i] = arr->data[i+1];
    arr->size--;
}

void array_replace_index(Array* arr, int index, const std::string& value){  // Принимаем строку
    if (index < 0 || index >= arr->size) throw std::out_of_range("Index out of range");
    arr->data[index] = value;       // Замена на строку
}

int array_len(Array* arr){ return arr->size; }

void array_print(Array* arr){
    for (int i = 0; i < arr->size; i++) std::cout << arr->data[i] << " ";
    std::cout << std::endl;
}

void array_free(Array* arr){
    delete[] arr->data;
    arr->data = nullptr;
    arr->size = arr->capacity = 0;
}