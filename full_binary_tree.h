#ifndef FULL_BINARY_TREE_H
#define FULL_BINARY_TREE_H

typedef struct TreeNode {
    int data;       // Значение узла 
    struct TreeNode* left;      // Указатель левого 
    struct TreeNode* right;     // Указатель правого 
} TreeNode;

typedef struct {
    TreeNode* root;     // Указатель на корневой узел 
} FullBinaryTree;

void fbt_init(FullBinaryTree* tree);
TreeNode* fbt_insert(TreeNode* root, int value);
bool fbt_search(TreeNode* root, int value);
bool fbt_is_full(TreeNode* root);
void fbt_print_inorder(TreeNode* root);
void fbt_free(TreeNode* root);

#endif