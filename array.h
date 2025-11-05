#ifndef ARRAY_H
#define ARRAY_H

typedef struct {
    int* data;  // Указатель на массив
    int size;   // Текущий размер
    int capacity;   // Максимальная вместимомть 
} Array;

void array_init(Array* arr, int capacity);
void array_add_back(Array* arr, int value);
void array_add_index(Array* arr, int index, int value);
int array_get_index(Array* arr, int index);
void array_remove_index(Array* arr, int index);
void array_replace_index(Array* arr, int index, int value);
int array_len(Array* arr);
void array_print(Array* arr);
void array_free(Array* arr);

#endif