#ifndef ARRAY_H
#define ARRAY_H

#include <string>  // Добавлен для использования строк

typedef struct {
    std::string* data;  // Указатель на массив строк
    int size;   // Текущий размер
    int capacity;   // Максимальная вместимость 
} Array;

void array_init(Array* arr, int capacity);
void array_add_back(Array* arr, const std::string& value);  
void array_add_index(Array* arr, int index, const std::string& value);  
std::string array_get_index(Array* arr, int index);  
void array_remove_index(Array* arr, int index);
void array_replace_index(Array* arr, int index, const std::string& value);  
int array_len(Array* arr);
void array_print(Array* arr);
void array_free(Array* arr);

#endif