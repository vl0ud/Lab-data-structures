#include "doubly_list.h"
#include <iostream>
#include <stdexcept>

void dl_init(DoublyList* list){
    list->head = list->tail = nullptr;      // Обнуляем показатели 
}

void dl_add_head(DoublyList* list, int value){
    DNode* newNode = new DNode{value, nullptr, nullptr};    // Новый узел
    if (!list->head) list->head = list->tail = newNode;     // Если пуст
    else {
        newNode->next = list->head;     // Новый узел на старую голову 
        list->head->prev = newNode;     // Старая голова на новый узел 
        list->head = newNode;       // Обновляем голову на newNode
    }
}

void dl_add_tail(DoublyList* list, int value){
    DNode* newNode = new DNode{value, nullptr, nullptr};
    if (!list->tail) list->head = list->tail = newNode;
    else {
        newNode->prev = list->tail;     // Новый указывает на старый 
        list->tail->next = newNode;     // Старый хвост на новый 
        list->tail = newNode;       // Обновляем хвост на новый node 
    }
}

void dl_add_before(DoublyList* list, int target, int value){
    if (!list->head) throw std::runtime_error("List is empty");
    DNode* current = list->head;
    while (current && current->data != target) current = current->next;     // Ищем таргет 
    if (!current) throw std::runtime_error("Target not found");
    DNode* newNode = new DNode{value, nullptr, nullptr};
    newNode->prev = current->prev;      // Новый узел указывает на предыдущий от current
    newNode->next = current;        // Новый узел указывает на current
    if (current->prev) current->prev->next = newNode;   // Обновляем следующий 
    else list->head = newNode;      // Обновляем голову 
    current->prev = newNode;        // Новый узел 
}

void dl_add_after(DoublyList* list, int target, int value){
    if (!list->head) throw std::runtime_error("List is empty");
    DNode* current = list->head;
    while (current && current->data != target) current = current->next;
    if (!current) throw std::runtime_error("Target not found");
    DNode* newNode = new DNode{value, nullptr, nullptr};
    newNode->next = current->next;      // Новый указывает на то, что после сurrent
    newNode->prev = current;        // Новый указывает на current
    if (current->next) current->next->prev = newNode;       // Если после current был другой, обновляем его prev
    else list->tail = newNode; 
    current->next = newNode;
}

void dl_remove_head(DoublyList* list){
    if (!list->head) throw std::runtime_error("List is empty");
    DNode* temp = list->head;       // Временная для головы 
    list->head = list->head->next;      // Перемещаем голову на след элемент
    if (list->head) list->head->prev = nullptr;     // обнуляем prev новой головы 
    else list->tail = nullptr;
    delete temp;
}

void dl_remove_tail(DoublyList* list){
    if (!list->tail) throw std::runtime_error("List is empty");
    DNode* temp = list->tail;
    list->tail = list->tail->prev;
    if (list->tail) list->tail->next = nullptr;
    else list->head = nullptr;
    delete temp;
}

void dl_remove_value(DoublyList* list, int value){
    if (!list->head) throw std::runtime_error("List is empty");
    DNode* current = list->head;
    while (current && current->data != value) current = current->next;
    if (!current) throw std::runtime_error("Value not found");
    if (current->prev) current->prev->next = current->next;     // Пропускаем 
    else list->head = current->next;        // Удаляем голову 
    if (current->next) current->next->prev = current->prev;     // Пропускаем
    else list->tail = current->prev;        // Уддаляем хвост 
    delete current;
}

bool dl_find(DoublyList* list, int value){
    DNode* current = list->head;
    while (current){
        if (current->data == value) return true;
        current = current->next;
    }
    return false;
}

void dl_print_forward(DoublyList* list){
    DNode* current = list->head;
    while (current){
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

void dl_print_backward(DoublyList* list){
    DNode* current = list->tail;
    while (current){
        std::cout << current->data << " ";
        current = current->prev;
    }
    std::cout << std::endl;
}

void dl_free(DoublyList* list){
    DNode* current = list->head;
    while (current){
        DNode* next = current->next;
        delete current;
        current = next;
    }
    list->head = list->tail = nullptr;
}