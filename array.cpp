#include "array.h"
#include <iostream>
#include <stdexcept>        // Либа для исключений

void array_init(Array* arr, int capacity){
    arr->data = new int[capacity];
    arr->size = 0;
    arr->capacity = capacity;
}

void array_add_back(Array* arr, int value){
    if (arr->size >= arr->capacity){    // Условие на переизбыток
        int new_capacity = arr->capacity * 2;
        int* new_data = new int[new_capacity];
        for (int i = 0; i < arr->size; i++) new_data[i] = arr->data[i];     // Перенос из старого участка памяти в новый
        delete[] arr->data;    // Освобождение старой памяти 
        arr->data = new_data;   // ОБНОВЛЕНИЕ УКАЗАТЕЛЕЙ
        arr->capacity = new_capacity;
    }
    arr->data[arr->size++] = value;     // Добавление элемента и увеличение текущего размера
}

void array_add_index(Array* arr, int index, int value){
    if (index < 0 || index > arr->size) throw std::out_of_range("Index out of range");      // Лежит ли индекс в диапазоне 
    if (arr->size >= arr->capacity){
        int new_capacity = arr->capacity * 2;
        int* new_data = new int[new_capacity];
        for (int i = 0; i < arr->size; i++) new_data[i] = arr->data[i];
        delete[] arr->data;
        arr->data = new_data;
        arr->capacity = new_capacity;
    }
    for (int i = arr->size; i > index; i--) arr->data[i] = arr->data[i-1];      // Сдвиг элементов вправо
    arr->data[index] = value;       // Вставка элемента
    arr->size++;
}

int array_get_index(Array* arr, int index){     
    if (index < 0 || index >= arr->size) throw std::out_of_range("Index out of range");
    return arr->data[index];
}

void array_remove_index(Array* arr, int index){
    if (index < 0 || index >= arr->size) throw std::out_of_range("Index out of range");
    for (int i = index; i < arr->size - 1; i++) arr->data[i] = arr->data[i+1];      // Сдвиг элементов влево
    arr->size--;
}

void array_replace_index(Array* arr, int index, int value){
    if (index < 0 || index >= arr->size) throw std::out_of_range("Index out of range");
    arr->data[index] = value;       // Замена значения 
}

int array_len(Array* arr){ return arr->size; }

void array_print(Array* arr){
    for (int i = 0; i < arr->size; i++) std::cout << arr->data[i] << " ";
    std::cout << std::endl;
}

void array_free(Array* arr){
    delete[] arr->data;
    arr->data = nullptr;        // Обнуление указателя 
    arr->size = arr->capacity = 0;      // Сброс параметров 
}