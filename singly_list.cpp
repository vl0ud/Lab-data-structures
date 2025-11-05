#include "singly_list.h"
#include <iostream>
#include <stdexcept>

void sl_init(SinglyList* list){
    list->head = list->tail = nullptr;
    list->size = 0;
}

void sl_add_head(SinglyList* list, int value){
    Node* newNode = new Node{value, nullptr};   // Создаем новый элемент 
    if (!list->head) list->head = list->tail = newNode;     // Если пуст -- newNode голова и хвост
    else {
        newNode->next = list->head;     // Замена обозначаем текущую голову next
        list->head = newNode;       // Голова = новая нода 
    }
    list->size++;
}

void sl_add_tail(SinglyList* list, int value){
    Node* newNode = new Node{value, nullptr};
    if (!list->tail) list->head = list->tail = newNode;
    else {
        list->tail->next = newNode;     // Обозначаем newnode как next 
        list->tail = newNode;       // Указатель newnode как хвост
    }
    list->size++;
}

void sl_add_before(SinglyList* list, int target, int value){
    if (!list->head) throw std::runtime_error("List is empty");     // Если пуст 
    if (list->head->data == target){    // Если голова
        sl_add_head(list, value);
        return;
    }
    Node* current = list->head;
    while (current->next && current->next->data != target) current = current->next;     // Поиск перед таргетом
    if (!current->next) throw std::runtime_error("Target not found");       // Если не найдено, ошибка 
    Node* newNode = new Node{value, current->next};     // Составляем указатели на вставку 
    current->next = newNode;
    list->size++;
}

void sl_add_after(SinglyList* list, int target, int value){
    if (!list->head) throw std::runtime_error("List is empty");
    Node* current = list->head;
    while (current && current->data != target) current = current->next;
    if (!current) throw std::runtime_error("Target not found");
    Node* newNode = new Node{value, current->next};
    current->next = newNode;
    if (current == list->tail) list->tail = newNode;
    list->size++;
}

void sl_remove_head(SinglyList* list){
    if (!list->head) throw std::runtime_error("List is empty");
    Node* temp = list->head;    // временная node для головы
    list->head = list->head->next;
    delete temp;
    if (!list->head) list->tail = nullptr;  // Если список стал пустым
    list->size--;
}

void sl_remove_tail(SinglyList* list){
    if (!list->head) throw std::runtime_error("List is empty");
    if (list->head == list->tail){  // Если один элемент
        delete list->head;
        list->head = list->tail = nullptr;
    } else {
        Node* current = list->head;
        while (current->next != list->tail) current = current->next;    // Идем до предпоследнего узла 
        delete list->tail;
        list->tail = current;
        list->tail->next = nullptr;
    }
    list->size--;
}

void sl_remove_value(SinglyList* list, int value){
    if (!list->head) throw std::runtime_error("List is empty");
    if (list->head->data == value){     // Если голова 
        sl_remove_head(list);
        return;
    }
    Node* current = list->head;
    while (current->next && current->next->data != value) current = current->next;
    if (!current->next) throw std::runtime_error("Value not found");
    Node* temp = current->next;
    current->next = temp->next;
    if (temp == list->tail) list->tail = current;
    delete temp;
    list->size--;
}

int sl_find(SinglyList* list, int value){
    Node* current = list->head;
    int index = 0;
    while (current){
        if (current->data == value) return index;
        current = current->next;
        index++;
    }
    return -1;
}

void sl_print(SinglyList* list){
    Node* current = list->head;
    while (current){
        std::cout << current->data << " -> ";
        current = current->next;
    }
    std::cout << "nullptr" << std::endl;
}

void sl_free(SinglyList* list){
    Node* current = list->head;
    while (current){
        Node* next = current->next;
        delete current;
        current = next;
    }
    list->head = list->tail = nullptr;
    list->size = 0;
}