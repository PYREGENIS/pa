#include <stdio.h>
#include <stdlib.h>

// Structura nodului
typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

int maxZigZag = 0;

// Funcție utilitară pentru a crea un nod
TreeNode* createNode(int val) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->val = val;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Direcții: 0 pentru Stânga, 1 pentru Dreapta
void findZigZag(TreeNode* node, int direction, int currentLength) {
    if (node == NULL) return;

    // Actualizăm lungimea maximă găsită până acum
    if (currentLength > maxZigZag) {
        maxZigZag = currentLength;
    }

    if (direction == 0) { // Am venit de la stânga
        // Continuăm ZigZag-ul mergând la DREAPTA
        findZigZag(node->right, 1, currentLength + 1);
        // Resetăm și începem un drum nou mergând la STÂNGA
        findZigZag(node->left, 0, 1);
    } else { // Am venit de la dreapta
        // Continuăm ZigZag-ul mergând la STÂNGA
        findZigZag(node->left, 0, currentLength + 1);
        // Resetăm și începem un drum nou mergând la DREAPTA
        findZigZag(node->right, 1, 1);
    }
}

int longestZigZag(TreeNode* root) {
    if (root == NULL) return 0;
    maxZigZag = 0;
    
    // Pornim explorarea în ambele direcții de la rădăcină
    findZigZag(root->left, 0, 1);
    findZigZag(root->right, 1, 1);
    
    return maxZigZag;
}

// Traversare în Preordine (Rădăcină - Stânga - Dreapta)
void preorder(TreeNode* root) {
    if (root == NULL) return;
    printf("%d ", root->val);
    preorder(root->left);
    preorder(root->right);
}

int main() {
    TreeNode* root = createNode(1);
    root->right = createNode(2);
    root->right->left = createNode(3);
    root->right->right = createNode(4);
    root->right->right->right = createNode(5);
    root->right->right->right->left = createNode(6);

    printf("Traversare Preordine: ");
    preorder(root);
    printf("\n");

    printf("Cea mai lunga cale ZigZag are lungimea: %d\n", longestZigZag(root));

    return 0;
}