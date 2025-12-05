#include "full_binary_tree.h"
#include <iostream>
#include <stdexcept>
#include <string>  // Добавлен для использования строк

void fbt_init(FullBinaryTree* tree){ tree->root = nullptr; }

bool is_complete(TreeNode* root, int index, int node_count){
    if (!root) return true;
    if (index >= node_count) return false;
    return is_complete(root->left, 2 * index + 1, node_count) &&
           is_complete(root->right, 2 * index + 2, node_count);
}

int count_nodes(TreeNode* root){
    if (!root) return 0;
    return 1 + count_nodes(root->left) + count_nodes(root->right);
}

TreeNode* insert_helper(TreeNode* root, const std::string& value, int index, int target_index){  // Принимаем строку
    if (!root){
        if (index == target_index){
            return new TreeNode{value, nullptr, nullptr};  // Создаем узел со строкой
        }
        return nullptr;
    }
    
    if (index == target_index){
        root->data = value;  // Устанавливаем строку
        return root;
    }
    
    TreeNode* left_result = insert_helper(root->left, value, 2 * index + 1, target_index);
    if (left_result){
        if (!root->left) root->left = left_result;
        return root;
    }
    
    TreeNode* right_result = insert_helper(root->right, value, 2 * index + 2, target_index);
    if (right_result){
        if (!root->right) root->right = right_result;
        return root;
    }
    
    return nullptr;
}

TreeNode* fbt_insert(TreeNode* root, const std::string& value){  // Принимаем строку
    if (!root) return new TreeNode{value, nullptr, nullptr};  // Создаем корень со строкой
    
    int node_count = count_nodes(root);
    return insert_helper(root, value, 0, node_count);
}

bool fbt_search(TreeNode* root, const std::string& value){  // Принимаем строку
    if (!root) return false;
    if (root->data == value) return true;  // Сравниваем строки
    return fbt_search(root->left, value) || fbt_search(root->right, value);
}

bool fbt_is_full(TreeNode* root){
    if (!root) return true;
    if (!root->left && !root->right) return true;
    if (root->left && root->right) return fbt_is_full(root->left) && fbt_is_full(root->right);
    return false;
}

void print_tree_helper(TreeNode* root, const std::string& prefix, bool is_left){
    if (!root) return;
    
    std::cout << prefix;
    std::cout << (is_left ? "├──" : "└──");
    
    // Вывод значения узла (строки)
    std::cout << root->data << std::endl;
    
    // Рекурсивный вывод потомков
    if (root->left || root->right){
        std::string new_prefix = prefix + (is_left ? "│   " : "    ");
        if (root->left) print_tree_helper(root->left, new_prefix, true);
        if (root->right) print_tree_helper(root->right, new_prefix, false);
    }
}

void fbt_print_inorder(TreeNode* root){
    if (!root){
        std::cout << "Дерево пустое" << std::endl;
        return;
    }
    
    std::cout << "Структура дерева:" << std::endl;
    print_tree_helper(root, "", false);
    
    // Дополнительно выводим симметричный обход в линейном виде
    std::cout << "Симметричный обход (inorder): ";
    fbt_print_inorder_linear(root);
    std::cout << std::endl;
}

// Линейный вывод строк
void fbt_print_inorder_linear(TreeNode* root){
    if (root){
        fbt_print_inorder_linear(root->left);
        std::cout << root->data << " ";  // Выводим строку
        fbt_print_inorder_linear(root->right);
    }
}

void fbt_free(TreeNode* root){
    if (root){
        fbt_free(root->left);
        fbt_free(root->right);
        delete root;
    }
}