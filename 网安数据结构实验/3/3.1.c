#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *left;
    struct Node *right;
} Node;

Node *CreateTree() {
    int x;
    scanf("%d", &x);
    if (x == -1) return NULL;

    Node *root = (Node*)malloc(sizeof(Node));
    root->val = x;
    root->left = CreateTree();
    root->right = CreateTree();
    return root;
}

void Insert(Node **root, int x) {
    if (!*root) {
        *root = (Node*)malloc(sizeof(Node));
        (*root)->val = x;
        (*root)->left = (*root)->right = NULL;
        return;
    }
    if ((*root)->val == x) return;
    if ((*root)->val > x) Insert(&(*root)->left, x);
    else Insert(&(*root)->right, x);
}

void MergeTrees(Node **t1, Node **t2) {
    if (*t2) {
        MergeTrees(t1, &(*t2)->left);
        Insert(t1, (*t2)->val);
        MergeTrees(t1, &(*t2)->right);
    }
}

void PrintInOrder(Node *root) {
    if (root) {
        PrintInOrder(root->left);
        printf("%d ", root->val);
        PrintInOrder(root->right);
    }
}

int main() {
    Node *t1 = CreateTree();
    Node *t2 = CreateTree();
    MergeTrees(&t1, &t2);
    PrintInOrder(t1);
    return 0;
}