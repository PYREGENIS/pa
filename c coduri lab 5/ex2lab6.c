#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode* createNode(int val) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void inorder(TreeNode* root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->val);
    inorder(root->right);
}

bool isBSTUtil(TreeNode* root, TreeNode* minNode, TreeNode* maxNode) {
    if (root == NULL) return true;
    if (minNode != NULL && root->val <= minNode->val) return false;
    if (maxNode != NULL && root->val >= maxNode->val) return false;
    
    return isBSTUtil(root->left, minNode, root) && 
           isBSTUtil(root->right, root, maxNode);
}

bool isBST(TreeNode* root) {
    return isBSTUtil(root, NULL, NULL);
}

int main() {
    TreeNode* root = createNode(4);
    root->left = createNode(2);
    root->right = createNode(6);
    root->left->left = createNode(1);
    root->left->right = createNode(3);

    printf("Traversare Inordine (la un BST corect trebuie sa fie sortata crescator): ");
    inorder(root);
    printf("\n");

    printf("Este arborele BST? %s\n", isBST(root) ? "Da" : "Nu");

    return 0;
}