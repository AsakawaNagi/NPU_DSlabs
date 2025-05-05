#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *left;
    struct Node *right;
} Node;

Node* createTree() {
    int x;
    scanf("%d", &x);
    if (x == -1) return NULL;

    Node* root = (Node*)malloc(sizeof(Node));
    root->val = x;
    root->left = createTree();
    root->right = createTree();
    return root;
}

int isBST(Node* root) {
    if (!root) return 1;

    if (root->left && root->left->val >= root->val) return 0;
    if (root->right && root->right->val <= root->val) return 0;

    return isBST(root->left) && isBST(root->right);
}

int main() {
    Node* root = createTree();
    printf(isBST(root) ? "yes" : "no");
    return 0;
}