#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>

#include "array.h"
#include "singly_list.h"
#include "doubly_list.h"
#include "stack.h"
#include "queue.h"
#include "full_binary_tree.h"

// Глобальные структуры данных
Array arr;
SinglyList sList;
DoublyList dList;
Stack stack;
Queue queue;
FullBinaryTree tree;

// Инициализация всех структур
void init_structures(){
    array_init(&arr, 10);
    sl_init(&sList);
    dl_init(&dList);
    stack_init(&stack, 10);
    queue_init(&queue);
    fbt_init(&tree);
}

// Загрузка данных из отдельных файлов для каждой структуры
void load_from_files(const std::string& base_filename){
    // Загрузка массива
    std::ifstream array_file(base_filename + "_array.txt");
    if (array_file.is_open()){
        std::string line;
        while (getline(array_file, line)){
            std::istringstream iss(line);
            std::string value;
            while (iss >> value) array_add_back(&arr, value);  // Читаем строки
        }
        array_file.close();
        std::cout << "Loaded array from " << base_filename << "_array.txt" << std::endl;
    }
    
    // Загрузка односвязного списка
    std::ifstream slist_file(base_filename + "_singly_list.txt");
    if (slist_file.is_open()){
        std::string line;
        while (getline(slist_file, line)){
            std::istringstream iss(line);
            std::string value;
            while (iss >> value) sl_add_tail(&sList, value);  // Читаем строки
        }
        slist_file.close();
        std::cout << "Loaded singly list from " << base_filename << "_singly_list.txt" << std::endl;
    }
    
    // Загрузка двусвязного списка
    std::ifstream dlist_file(base_filename + "_doubly_list.txt");
    if (dlist_file.is_open()){
        std::string line;
        while (getline(dlist_file, line)){
            std::istringstream iss(line);
            std::string value;
            while (iss >> value) dl_add_tail(&dList, value);  // Читаем строки
        }
        dlist_file.close();
        std::cout << "Loaded doubly list from " << base_filename << "_doubly_list.txt" << std::endl;
    }
    
    // Загрузка стека
    std::ifstream stack_file(base_filename + "_stack.txt");
    if (stack_file.is_open()){
        std::string line;
        while (getline(stack_file, line)){
            std::istringstream iss(line);
            std::string value;
            while (iss >> value) stack_push(&stack, value);  // Читаем строки
        }
        stack_file.close();
        std::cout << "Loaded stack from " << base_filename << "_stack.txt" << std::endl;
    }
    
    // Загрузка очереди
    std::ifstream queue_file(base_filename + "_queue.txt");
    if (queue_file.is_open()){
        std::string line;
        while (getline(queue_file, line)){
            std::istringstream iss(line);
            std::string value;
            while (iss >> value) queue_enqueue(&queue, value);  // Читаем строки
        }
        queue_file.close();
        std::cout << "Loaded queue from " << base_filename << "_queue.txt" << std::endl;
    }
    
    // Загрузка дерева
    std::ifstream tree_file(base_filename + "_tree.txt");
    if (tree_file.is_open()){
        std::string line;
        while (getline(tree_file, line)){
            std::istringstream iss(line);
            std::string value;
            while (iss >> value) tree.root = fbt_insert(tree.root, value);  // Читаем строки
        }
        tree_file.close();
        std::cout << "Loaded tree from " << base_filename << "_tree.txt" << std::endl;
    }
}

// Сохранение данных в отдельные файлы для каждой структуры
void save_to_files(const std::string& base_filename){
    // Сохраняем массив
    std::ofstream array_file(base_filename + "_array.txt");
    for (int i = 0; i < array_len(&arr); i++){
        array_file << array_get_index(&arr, i) << " ";  // Записываем строки
    }
    array_file.close();
    std::cout << "Saved array to " << base_filename << "_array.txt" << std::endl;
    
    // Сохраняем односвязный список
    std::ofstream slist_file(base_filename + "_singly_list.txt");
    Node* current = sList.head;
    while (current){
        slist_file << current->data << " ";  // Записываем строки
        current = current->next;
    }
    slist_file.close();
    std::cout << "Saved singly list to " << base_filename << "_singly_list.txt" << std::endl;
    
    // Сохраняем двусвязный список
    std::ofstream dlist_file(base_filename + "_doubly_list.txt");
    DNode* dcurrent = dList.head;
    while (dcurrent){
        dlist_file << dcurrent->data << " ";  // Записываем строки
        dcurrent = dcurrent->next;
    }
    dlist_file.close();
    std::cout << "Saved doubly list to " << base_filename << "_doubly_list.txt" << std::endl;
    
    // Сохраняем стек
    std::ofstream stack_file(base_filename + "_stack.txt");
    Stack temp_stack;
    stack_init(&temp_stack, stack.capacity);
    
    // Копируем стек для сохранения порядка
    while (!stack_empty(&stack)){
        std::string val = stack_pop(&stack);  // Получаем строку
        stack_push(&temp_stack, val);
    }
    
    // Восстанавливаем стек и сохраняем
    while (!stack_empty(&temp_stack)){
        std::string val = stack_pop(&temp_stack);
        stack_file << val << " ";  // Записываем строку
        stack_push(&stack, val);
    }
    stack_file.close();
    stack_free(&temp_stack);
    std::cout << "Saved stack to " << base_filename << "_stack.txt" << std::endl;
    
    // Сохраняем очередь
    std::ofstream queue_file(base_filename + "_queue.txt");
    Queue temp_queue;
    queue_init(&temp_queue);
    
    // Копируем очередь для сохранения порядка
    while (!queue_empty(&queue)){
        std::string val = queue_dequeue(&queue);  // Получаем строку
        queue_file << val << " ";  // Записываем строку
        queue_enqueue(&temp_queue, val);
    }
    
    // Восстанавливаем очередь
    while (!queue_empty(&temp_queue)){
        std::string val = queue_dequeue(&temp_queue);
        queue_enqueue(&queue, val);
    }
    queue_file.close();
    queue_free(&temp_queue);
    std::cout << "Saved queue to " << base_filename << "_queue.txt" << std::endl;
    
    // Сохраняем дерево (inorder)
    std::ofstream tree_file(base_filename + "_tree.txt");
    std::vector<std::string> tree_values;
    
    // Функция для сбора значений дерева
    std::function<void(TreeNode*)> collect_values = [&](TreeNode* node){
        if (!node) return;
        collect_values(node->left);
        tree_values.push_back(node->data);  // Сохраняем строку
        collect_values(node->right);
    };
    
    collect_values(tree.root);
    for (const std::string& val : tree_values) tree_file << val << " ";  // Записываем строки
    tree_file.close();
    std::cout << "Saved tree to " << base_filename << "_tree.txt" << std::endl;
}

// Обработка команд
void process_command(const std::string& query){
    std::istringstream iss(query);
    std::string command;
    iss >> command;
    
    // Преобразуем команду в верхний регистр
    std::transform(command.begin(), command.end(), command.begin(), ::toupper);
    
    try {
        // Команды для массива
        if (command == "MPUSH_BACK"){
            std::string value;
            iss >> value;
            array_add_back(&arr, value);
            std::cout << "Added \"" << value << "\" to array" << std::endl;
        }
        else if (command == "MPUSH_INDEX"){
            int index;
            std::string value;
            iss >> index >> value;
            array_add_index(&arr, index, value);
            std::cout << "Added \"" << value << "\" at index " << index << std::endl;
        }
        else if (command == "MDEL"){
            int index;
            iss >> index;
            array_remove_index(&arr, index);
            std::cout << "Removed element at index " << index << std::endl;
        }
        else if (command == "MGET"){
            int index;
            iss >> index;
            std::string value = array_get_index(&arr, index);
            std::cout << "Array[" << index << "] = \"" << value << "\"" << std::endl;
        }
        else if (command == "MREPLACE"){
            int index;
            std::string value;
            iss >> index >> value;
            array_replace_index(&arr, index, value);
            std::cout << "Replaced array[" << index << "] with \"" << value << "\"" << std::endl;
        }
        else if (command == "MLEN"){
            std::cout << "Array length: " << array_len(&arr) << std::endl;
        }
        else if (command == "MPRINT"){
            std::cout << "Array: ";
            array_print(&arr);
        }
        
        // Команды для односвязного списка
        else if (command == "FPUSH_HEAD"){
            std::string value;
            iss >> value;
            sl_add_head(&sList, value);
            std::cout << "Added \"" << value << "\" to list head" << std::endl;
        }
        else if (command == "FPUSH_TAIL"){
            std::string value;
            iss >> value;
            sl_add_tail(&sList, value);
            std::cout << "Added \"" << value << "\" to list tail" << std::endl;
        }
        else if (command == "FPUSH_BEFORE"){
            std::string target, value;
            iss >> target >> value;
            sl_add_before(&sList, target, value);
            std::cout << "Added \"" << value << "\" before \"" << target << "\"" << std::endl;
        }
        else if (command == "FPUSH_AFTER"){
            std::string target, value;
            iss >> target >> value;
            sl_add_after(&sList, target, value);
            std::cout << "Added \"" << value << "\" after \"" << target << "\"" << std::endl;
        }
        else if (command == "FDEL_HEAD"){
            sl_remove_head(&sList);
            std::cout << "Removed list head" << std::endl;
        }
        else if (command == "FDEL_TAIL"){
            sl_remove_tail(&sList);
            std::cout << "Removed list tail" << std::endl;
        }
        else if (command == "FDEL_VALUE"){
            std::string value;
            iss >> value;
            sl_remove_value(&sList, value);
            std::cout << "Removed value \"" << value << "\" from list" << std::endl;
        }
        else if (command == "FSEARCH"){
            std::string value;
            iss >> value;
            int index = sl_find(&sList, value);
            if (index != -1){
                std::cout << "Value \"" << value << "\" found at index " << index << std::endl;
            } else {
                std::cout << "Value \"" << value << "\" not found" << std::endl;
            }
        }
        else if (command == "FPRINT"){
            std::cout << "Singly List: ";
            sl_print(&sList);
        }
        
        // Команды для двусвязного списка
        else if (command == "LPUSH_HEAD"){
            std::string value;
            iss >> value;
            dl_add_head(&dList, value);
            std::cout << "Added \"" << value << "\" to doubly list head" << std::endl;
        }
        else if (command == "LPUSH_TAIL"){
            std::string value;
            iss >> value;
            dl_add_tail(&dList, value);
            std::cout << "Added \"" << value << "\" to doubly list tail" << std::endl;
        }
        else if (command == "LPUSH_BEFORE"){
            std::string target, value;
            iss >> target >> value;
            dl_add_before(&dList, target, value);
            std::cout << "Added \"" << value << "\" before \"" << target << "\"" << std::endl;
        }
        else if (command == "LPUSH_AFTER"){
            std::string target, value;
            iss >> target >> value;
            dl_add_after(&dList, target, value);
            std::cout << "Added \"" << value << "\" after \"" << target << "\"" << std::endl;
        }
        else if (command == "LDEL_HEAD"){
            dl_remove_head(&dList);
            std::cout << "Removed doubly list head" << std::endl;
        }
        else if (command == "LDEL_TAIL"){
            dl_remove_tail(&dList);
            std::cout << "Removed doubly list tail" << std::endl;
        }
        else if (command == "LDEL_VALUE"){
            std::string value;
            iss >> value;
            dl_remove_value(&dList, value);
            std::cout << "Removed value \"" << value << "\" from doubly list" << std::endl;
        }
        else if (command == "LSEARCH"){
            std::string value;
            iss >> value;
            bool found = dl_find(&dList, value);
            std::cout << "Value \"" << value << "\" " << (found ? "found" : "not found") << std::endl;
        }
        else if (command == "LPRINT_FORWARD"){
            std::cout << "Doubly List (forward): ";
            dl_print_forward(&dList);
        }
        else if (command == "LPRINT_BACKWARD"){
            std::cout << "Doubly List (backward): ";
            dl_print_backward(&dList);
        }
        
        // Команды для стека
        else if (command == "SPUSH"){
            std::string value;
            iss >> value;
            stack_push(&stack, value);
            std::cout << "Pushed \"" << value << "\" to stack" << std::endl;
        }
        else if (command == "SPOP"){
            std::string value = stack_pop(&stack);
            std::cout << "Popped from stack: \"" << value << "\"" << std::endl;
        }
        else if (command == "SPEEK"){
            std::string value = stack_peek(&stack);
            std::cout << "Stack top: \"" << value << "\"" << std::endl;
        }
        else if (command == "SEMPTY"){
            bool empty = stack_empty(&stack);
            std::cout << "Stack is " << (empty ? "empty" : "not empty") << std::endl;
        }
        else if (command == "SPRINT"){
            std::cout << "Stack: ";
            Stack temp;
            stack_init(&temp, stack.capacity);
            
            while (!stack_empty(&stack)){
                std::string val = stack_pop(&stack);
                std::cout << val << " ";
                stack_push(&temp, val);
            }
            std::cout << std::endl;
            
            while (!stack_empty(&temp)){
                std::string val = stack_pop(&temp);
                stack_push(&stack, val);
            }
            stack_free(&temp);
        }
        
        // Команды для очереди
        else if (command == "QPUSH"){
            std::string value;
            iss >> value;
            queue_enqueue(&queue, value);
            std::cout << "Enqueued \"" << value << "\"" << std::endl;
        }
        else if (command == "QPOP"){
            std::string value = queue_dequeue(&queue);
            std::cout << "Dequeued: \"" << value << "\"" << std::endl;
        }
        else if (command == "QPEEK"){
            std::string value = queue_peek(&queue);
            std::cout << "Queue front: \"" << value << "\"" << std::endl;
        }
        else if (command == "QEMPTY"){
            bool empty = queue_empty(&queue);
            std::cout << "Queue is " << (empty ? "empty" : "not empty") << std::endl;
        }
        else if (command == "QPRINT"){
            std::cout << "Queue: ";
            Queue temp;
            queue_init(&temp);
            
            while (!queue_empty(&queue)){
                std::string val = queue_dequeue(&queue);
                std::cout << val << " ";
                queue_enqueue(&temp, val);
            }
            std::cout << std::endl;
            
            while (!queue_empty(&temp)){
                std::string val = queue_dequeue(&temp);
                queue_enqueue(&queue, val);
            }
            queue_free(&temp);
        }
        
        // Команды для дерева
        else if (command == "TINSERT"){
            std::string value;
            iss >> value;
            tree.root = fbt_insert(tree.root, value);
            std::cout << "Inserted \"" << value << "\" into tree" << std::endl;
        }
        else if (command == "TSEARCH"){
            std::string value;
            iss >> value;
            bool found = fbt_search(tree.root, value);
            std::cout << "Value \"" << value << "\" " << (found ? "found" : "not found") << " in tree" << std::endl;
        }
        else if (command == "TISFULL"){
            bool is_full = fbt_is_full(tree.root);
            std::cout << "Tree is " << (is_full ? "full" : "not full") << std::endl;
        }
        else if (command == "TPRINT"){
            std::cout << "Tree (inorder): ";
            fbt_print_inorder(tree.root);
            std::cout << std::endl;
        }
        
        else {
            std::cout << "Unknown command: " << command << std::endl;
            std::cout << "Available commands: " << std::endl;
            std::cout << "Array: MPUSH_BACK, MPUSH_INDEX, MDEL, MGET, MREPLACE, MLEN, MPRINT" << std::endl;
            std::cout << "Singly List: FPUSH_HEAD, FPUSH_TAIL, FPUSH_BEFORE, FPUSH_AFTER, FDEL_HEAD, FDEL_TAIL, FDEL_VALUE, FSEARCH, FPRINT" << std::endl;
            std::cout << "Doubly List: LPUSH_HEAD, LPUSH_TAIL, LPUSH_BEFORE, LPUSH_AFTER, LDEL_HEAD, LDEL_TAIL, LDEL_VALUE, LSEARCH, LPRINT_FORWARD, LPRINT_BACKWARD" << std::endl;
            std::cout << "Stack: SPUSH, SPOP, SPEEK, SEMPTY, SPRINT" << std::endl;
            std::cout << "Queue: QPUSH, QPOP, QPEEK, QEMPTY, QPRINT" << std::endl;
            std::cout << "Tree: TINSERT, TSEARCH, TISFULL, TPRINT" << std::endl;
        }
    }
    catch (const std::exception& e){
        std::cout << "Error: " << e.what() << std::endl;
    }
}

int main(int argc, char* argv[]){
    if (argc != 5){
        std::cout << "Usage: " << argv[0] << " --file <filename> --query <command>" << std::endl;
        std::cout << "Example: " << argv[0] << " --file data --query 'MPUSH_BACK \"hello\"'" << std::endl;
        return 1;
    }
    
    std::string base_filename, query;
    
    for (int i = 1; i < argc; i++){
        std::string arg = argv[i];
        if (arg == "--file" && i + 1 < argc) base_filename = argv[++i];
        else if (arg == "--query" && i + 1 < argc) query = argv[++i];
    }
    
    if (base_filename.empty() || query.empty()){
        std::cout << "Error: Missing required arguments" << std::endl;
        return 1;
    }
    
    // Инициализация структур
    init_structures();
    
    // Загрузка данных из файлов
    load_from_files(base_filename);
    
    // Выполнение команды
    process_command(query);
    
    // Сохранение данных в файлы
    save_to_files(base_filename);
    
    // Освобождение памяти
    array_free(&arr);
    sl_free(&sList);
    dl_free(&dList);
    stack_free(&stack);
    queue_free(&queue);
    fbt_free(tree.root);
    
    return 0;
}