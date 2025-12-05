#ifndef SINGLY_LIST_H
#define SINGLY_LIST_H

#include <string>  // Добавлен для использования строк

typedef struct Node {
    std::string data;   // Значение узла - строка
    struct Node* next;  // Указатель на следующий узел 
} Node;

typedef struct {
    Node* head;     // Указатель на первый узел
    Node* tail;     // Указатель на последний узел
    int size;       // Кол-во элементов в списке
} SinglyList;

void sl_init(SinglyList* list);
void sl_add_head(SinglyList* list, const std::string& value);  
void sl_add_tail(SinglyList* list, const std::string& value);  
void sl_add_before(SinglyList* list, const std::string& target, const std::string& value);
void sl_add_after(SinglyList* list, const std::string& target, const std::string& value);  
void sl_remove_head(SinglyList* list);
void sl_remove_tail(SinglyList* list);
void sl_remove_value(SinglyList* list, const std::string& value);
int sl_find(SinglyList* list, const std::string& value); 
void sl_print(SinglyList* list);
void sl_free(SinglyList* list);

#endif