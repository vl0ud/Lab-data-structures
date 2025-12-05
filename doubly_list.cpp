#include "doubly_list.h"
#include <iostream>
#include <stdexcept>
#include <string>

void dl_init(DoublyList* list){
    list->head = list->tail = nullptr;
}

void dl_add_head(DoublyList* list, const std::string& value){  // Принимаем строку
    DNode* newNode = new DNode{value, nullptr, nullptr};  // Создаем узел со строкой
    if (!list->head) list->head = list->tail = newNode;
    else {
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    }
}

void dl_add_tail(DoublyList* list, const std::string& value){  // Принимаем строку
    DNode* newNode = new DNode{value, nullptr, nullptr};  // Создаем узел со строкой
    if (!list->tail) list->head = list->tail = newNode;
    else {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

void dl_add_before(DoublyList* list, const std::string& target, const std::string& value){  // Принимаем строки
    if (!list->head) throw std::runtime_error("List is empty");
    DNode* current = list->head;
    while (current && current->data != target) current = current->next;  // Сравниваем строки
    if (!current) throw std::runtime_error("Target not found");
    DNode* newNode = new DNode{value, nullptr, nullptr};  // Создаем узел со строкой
    newNode->prev = current->prev;
    newNode->next = current;
    if (current->prev) current->prev->next = newNode;
    else list->head = newNode;
    current->prev = newNode;
}

void dl_add_after(DoublyList* list, const std::string& target, const std::string& value){  // Принимаем строки
    if (!list->head) throw std::runtime_error("List is empty");
    DNode* current = list->head;
    while (current && current->data != target) current = current->next;  // Сравниваем строки
    if (!current) throw std::runtime_error("Target not found");
    DNode* newNode = new DNode{value, nullptr, nullptr};  // Создаем узел со строкой
    newNode->next = current->next;
    newNode->prev = current;
    if (current->next) current->next->prev = newNode;
    else list->tail = newNode;
    current->next = newNode;
}

void dl_remove_head(DoublyList* list){
    if (!list->head) throw std::runtime_error("List is empty");
    DNode* temp = list->head;
    list->head = list->head->next;
    if (list->head) list->head->prev = nullptr;
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

void dl_remove_value(DoublyList* list, const std::string& value){  // Принимаем строку
    if (!list->head) throw std::runtime_error("List is empty");
    DNode* current = list->head;
    while (current && current->data != value) current = current->next;  // Сравниваем строки
    if (!current) throw std::runtime_error("Value not found");
    if (current->prev) current->prev->next = current->next;
    else list->head = current->next;
    if (current->next) current->next->prev = current->prev;
    else list->tail = current->prev;
    delete current;
}

bool dl_find(DoublyList* list, const std::string& value){  // Принимаем строку
    DNode* current = list->head;
    while (current){
        if (current->data == value) return true;  // Сравниваем строки
        current = current->next;
    }
    return false;
}

void dl_print_forward(DoublyList* list){
    DNode* current = list->head;
    while (current){
        std::cout << current->data << " ";  // Выводим строку
        current = current->next;
    }
    std::cout << std::endl;
}

void dl_print_backward(DoublyList* list){
    DNode* current = list->tail;
    while (current){
        std::cout << current->data << " ";  // Выводим строку
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