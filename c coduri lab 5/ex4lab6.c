#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void preorder(TreeNode* root) {
    if (root == NULL) return;
    printf("%d ", root->val);
    preorder(root->left);
    preorder(root->right);
}

void serializeHelper(TreeNode* root, char* str) {
    if (root == NULL) {
        strcat(str, "N,");
        return;
    }
    char buffer[20];
    sprintf(buffer, "%d,", root->val);
    strcat(str, buffer);
    serializeHelper(root->left, str);
    serializeHelper(root->right, str);
}

char* serialize(TreeNode* root) {
    char* str = (char*)calloc(1000, sizeof(char));
    serializeHelper(root, str);
    return str;
}

TreeNode* deserializeHelper(char** str_ptr) {
    if (**str_ptr == '\0') return NULL;
    
    char* comma = strchr(*str_ptr, ',');
    if (comma == NULL) return NULL;
    
    *comma = '\0';
    char* token = *str_ptr;
    *str_ptr = comma + 1; 
    
    if (strcmp(token, "N") == 0) return NULL;
    
    TreeNode* node = createNode(atoi(token));
    node->left = deserializeHelper(str_ptr);
    node->right = deserializeHelper(str_ptr);
    
    return node;
}

TreeNode* deserialize(char* data) {
    char* ptr = data;
    return deserializeHelper(&ptr);
}

int main() {
    TreeNode* root = createNode(4);
    root->left = createNode(2);
    root->right = createNode(6);

    char* serializedStr = serialize(root);
    printf("Arbore transformat in string: %s\n", serializedStr);
    
    TreeNode* deserializedRoot = deserialize(serializedStr);
    printf("Verificare arbore refacut (Preordine): ");
    preorder(deserializedRoot);
    printf("\n");
    
    free(serializedStr);
    return 0;
}