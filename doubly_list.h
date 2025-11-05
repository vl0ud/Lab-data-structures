#ifndef DOUBLY_LIST_H
#define DOUBLY_LIST_H

typedef struct DNode {
    int data;       // значение узла 
    struct DNode* prev;     // Указатель на предыдущий 
    struct DNode* next;     // Указатель на следующий 
    
} DNode;

typedef struct {
    DNode* head;
    DNode* tail;
} DoublyList;

void dl_init(DoublyList* list);
void dl_add_head(DoublyList* list, int value);
void dl_add_tail(DoublyList* list, int value);
void dl_add_before(DoublyList* list, int target, int value);
void dl_add_after(DoublyList* list, int target, int value);
void dl_remove_head(DoublyList* list);
void dl_remove_tail(DoublyList* list);
void dl_remove_value(DoublyList* list, int value);
bool dl_find(DoublyList* list, int value);
void dl_print_forward(DoublyList* list);
void dl_print_backward(DoublyList* list);
void dl_free(DoublyList* list);

#endif