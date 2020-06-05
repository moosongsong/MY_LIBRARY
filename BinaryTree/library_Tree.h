#ifndef MY_LIBRARY_LIBRARY_TREE_H
#define MY_LIBRARY_LIBRARY_TREE_H

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct Tree {
    Node *root;
    int count;
} Tree;

typedef int errno_t;

errno_t bstInsert(Tree *tree, int data);

void bstDisplay(Tree *tree);
static void _preorder(Node* node);
void preorder(Tree * tree);
#endif //MY_LIBRARY_LIBRARY_TREE_H
