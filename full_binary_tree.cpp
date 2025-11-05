#include "full_binary_tree.h"
#include <iostream>
#include <stdexcept>

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

TreeNode* insert_helper(TreeNode* root, int value, int index, int target_index){
    if (!root){
        if (index == target_index){
            return new TreeNode{value, nullptr, nullptr};
        }
        return nullptr;
    }
    
    if (index == target_index){
        root->data = value;
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

TreeNode* fbt_insert(TreeNode* root, int value){        // Функция вставки
    if (!root) return new TreeNode{value, nullptr, nullptr};
    
    int node_count = count_nodes(root);
    return insert_helper(root, value, 0, node_count);
}

bool fbt_search(TreeNode* root, int value){     // Рекурсивный поиск 
    if (!root) return false;
    if (root->data == value) return true;
    return fbt_search(root->left, value) || fbt_search(root->right, value);
}

bool fbt_is_full(TreeNode* root){
    if (!root) return true;
    if (!root->left && !root->right) return true;
    if (root->left && root->right) return fbt_is_full(root->left) && fbt_is_full(root->right);
    return false;
}

void fbt_print_inorder(TreeNode* root){     // Симметричный обход
    if (root){
        fbt_print_inorder(root->left);
        std::cout << root->data << " ";
        fbt_print_inorder(root->right);
    }
}

void fbt_free(TreeNode* root){
    if (root){
        fbt_free(root->left);
        fbt_free(root->right);
        delete root;
    }
}