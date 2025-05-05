#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char val;
    struct Node *left, *right;
} Node;

// A(B(#,D),C(E(#,F),#))
// 递归这里是

void createTree(Node *root) {
    char c1 = getchar(), c2 = getchar();
    root->left = root->right = NULL;

    if (c1 == ',') {
        root->val = c2;
        if (getchar() == '(') {
            root->left = malloc(sizeof(Node));
            root->right = malloc(sizeof(Node));
            createTree(root->left);
            createTree(root->right);
        }
    } else {
        root->val = c1;
        if (c2 == '(') {
            root->left = malloc(sizeof(Node));
            root->right = malloc(sizeof(Node));
            createTree(root->left);
            createTree(root->right);
        }
    }
}

// AB#DCE#F# 还是递归
void preOrder(Node *root) {
    if (!root) return;
    putchar(root->val);
    preOrder(root->left);
    preOrder(root->right);
}

int main() {
    Node *root = malloc(sizeof(Node));
    createTree(root);
    preOrder(root);
    return 0;
}