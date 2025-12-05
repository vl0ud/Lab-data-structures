#ifndef FULL_BINARY_TREE_H
#define FULL_BINARY_TREE_H

#include <string>  // Добавлен для использования строк

typedef struct TreeNode {
    std::string data;       // Значение узла - строка
    struct TreeNode* left;      // Указатель левого 
    struct TreeNode* right;     // Указатель правого 
} TreeNode;

typedef struct {
    TreeNode* root;     // Указатель на корневой узел 
} FullBinaryTree;

void fbt_init(FullBinaryTree* tree);
TreeNode* fbt_insert(TreeNode* root, const std::string& value);  // Изменено на строку
bool fbt_search(TreeNode* root, const std::string& value);  // Изменено на строку
bool fbt_is_full(TreeNode* root);
void fbt_print_inorder(TreeNode* root);
void fbt_free(TreeNode* root);
void fbt_print_inorder_linear(TreeNode* root); 
void print_tree_helper(TreeNode* root);

#endif