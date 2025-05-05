#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char val;
    struct Node *left, *right;
} Node;

Node* createTree() {
    char c = getchar();
    if (c == '#') return NULL;

    Node *n = malloc(sizeof(Node));
    n->val = c;
    n->left = createTree();
    n->right = createTree();
    return n;
}

void inOrder(Node *n) {
    if (!n) return;
    inOrder(n->left);
    putchar(n->val);
    inOrder(n->right);
}

int main() {
    Node *root = createTree();
    inOrder(root);
    return 0;
}