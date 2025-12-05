#include "singly_list.h"
#include <iostream>
#include <stdexcept>
#include <string> 

void sl_init(SinglyList* list){
    list->head = list->tail = nullptr;
    list->size = 0;
}

void sl_add_head(SinglyList* list, const std::string& value){  // Принимаем строку
    Node* newNode = new Node{value, nullptr};   // Создаем новый элемент со строкой
    if (!list->head) list->head = list->tail = newNode;
    else {
        newNode->next = list->head;
        list->head = newNode;
    }
    list->size++;
}

void sl_add_tail(SinglyList* list, const std::string& value){  // Принимаем строку
    Node* newNode = new Node{value, nullptr};  // Создаем новый элемент со строкой
    if (!list->tail) list->head = list->tail = newNode;
    else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
    list->size++;
}

void sl_add_before(SinglyList* list, const std::string& target, const std::string& value){  // Принимаем строки
    if (!list->head) throw std::runtime_error("List is empty");
    if (list->head->data == target){    // Сравниваем строки
        sl_add_head(list, value);
        return;
    }
    Node* current = list->head;
    while (current->next && current->next->data != target) current = current->next;  // Сравниваем строки
    if (!current->next) throw std::runtime_error("Target not found");
    Node* newNode = new Node{value, current->next};  // Создаем узел со строкой
    current->next = newNode;
    list->size++;
}

void sl_add_after(SinglyList* list, const std::string& target, const std::string& value){  // Принимаем строки
    if (!list->head) throw std::runtime_error("List is empty");
    Node* current = list->head;
    while (current && current->data != target) current = current->next;  // Сравниваем строки
    if (!current) throw std::runtime_error("Target not found");
    Node* newNode = new Node{value, current->next};  // Создаем узел со строкой
    current->next = newNode;
    if (current == list->tail) list->tail = newNode;
    list->size++;
}

void sl_remove_head(SinglyList* list){
    if (!list->head) throw std::runtime_error("List is empty");
    Node* temp = list->head;
    list->head = list->head->next;
    delete temp;
    if (!list->head) list->tail = nullptr;
    list->size--;
}

void sl_remove_tail(SinglyList* list){
    if (!list->head) throw std::runtime_error("List is empty");
    if (list->head == list->tail){
        delete list->head;
        list->head = list->tail = nullptr;
    } else {
        Node* current = list->head;
        while (current->next != list->tail) current = current->next;
        delete list->tail;
        list->tail = current;
        list->tail->next = nullptr;
    }
    list->size--;
}

void sl_remove_value(SinglyList* list, const std::string& value){  // Принимаем строку
    if (!list->head) throw std::runtime_error("List is empty");
    if (list->head->data == value){  // Сравниваем строки
        sl_remove_head(list);
        return;
    }
    Node* current = list->head;
    while (current->next && current->next->data != value) current = current->next;  // Сравниваем строки
    if (!current->next) throw std::runtime_error("Value not found");
    Node* temp = current->next;
    current->next = temp->next;
    if (temp == list->tail) list->tail = current;
    delete temp;
    list->size--;
}

int sl_find(SinglyList* list, const std::string& value){  // Принимаем строку
    Node* current = list->head;
    int index = 0;
    while (current){
        if (current->data == value) return index;  // Сравниваем строки
        current = current->next;
        index++;
    }
    return -1;
}

void sl_print(SinglyList* list){
    Node* current = list->head;
    while (current){
        std::cout << current->data << " -> ";  // Выводим строку
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