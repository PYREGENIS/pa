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

void getDepthAndParent(TreeNode* root, int target, int depth, TreeNode* parent, int* outDepth, TreeNode** outParent) {
    if (root == NULL) return;
    if (root->val == target) {
        *outDepth = depth;
        *outParent = parent;
        return;
    }
    getDepthAndParent(root->left, target, depth + 1, root, outDepth, outParent);
    getDepthAndParent(root->right, target, depth + 1, root, outDepth, outParent);
}

bool isCousins(TreeNode* root, int x, int y) {
    int xDepth = -1, yDepth = -1;
    TreeNode *xParent = NULL, *yParent = NULL;
    
    getDepthAndParent(root, x, 0, NULL, &xDepth, &xParent);
    getDepthAndParent(root, y, 0, NULL, &yDepth, &yParent);
    
    return (xDepth == yDepth) && (xParent != yParent) && (xParent != NULL);
}

int main() {
    TreeNode* root = createNode(4);
    root->left = createNode(2);
    root->right = createNode(6);
    root->left->left = createNode(1);
    root->right->right = createNode(7);

    printf("Traversare Inordine: ");
    inorder(root);
    printf("\n");

    // Nodurile 1 si 7 sunt la fel de adanci (nivel 2), dar au parinti diferiti (2 si 6)
    printf("Sunt nodurile 1 si 7 veri? %s\n", isCousins(root, 1, 7) ? "Da" : "Nu");
    
    // Nodurile 2 si 6 au acelasi parinte (4), deci sunt frati, nu veri
    printf("Sunt nodurile 2 si 6 veri? %s\n", isCousins(root, 2, 6) ? "Da" : "Nu");

    return 0;
}
