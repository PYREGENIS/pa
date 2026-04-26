#include <stdio.h>
#include <stdlib.h>

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

void postorder(TreeNode* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->val);
}

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == NULL || root == p || root == q) return root;
    
    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);
    
    if (left != NULL && right != NULL) return root;
    return (left != NULL) ? left : right;
}

int main() {
    TreeNode* root = createNode(4);
    root->left = createNode(2);
    root->right = createNode(6);
    root->left->left = createNode(1);
    root->left->right = createNode(3);

    printf("Traversare Postordine: ");
    postorder(root);
    printf("\n");

    TreeNode* p = root->left->left;   // nodul 1
    TreeNode* q = root->left->right;  // nodul 3
    TreeNode* lca = lowestCommonAncestor(root, p, q);
    
    printf("Cel mai apropiat stramos comun pentru %d si %d este: %d\n", p->val, q->val, lca->val);

    return 0;
}