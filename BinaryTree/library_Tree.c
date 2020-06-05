#include "library_Tree.h"
#include <stdio.h>
#include <stdlib.h>
int dep [10];
int temp = -1;
errno_t bstInsert(Tree * tree, int data) {
    Node* node = calloc(1, sizeof(Node));
    if (node == NULL) {
        perror("bstInsert");
        return -1;
    }

    Node * root = tree->root;
    node->data = data;
    if (root == NULL) {	// 트리가 비어 있는 경우
        root = node;
        return 0;
    }

    Node* parent = NULL;
    Node* cur = root;
    while (cur != NULL) {
        parent = cur;
        if (data < cur->data)
            cur = cur->left;
        else if (data > cur->data)
            cur = cur->right;
        else {
            free(node);
            return -1;
        }
    }
    if (data < parent->data) parent->left = node;
    else parent->right = node;
    return 0;
}

static void _preorder(Node* node) {
    temp++;
    if (node == NULL){
        temp--;
        return;
    }
    printf("%d\n", node->data);
    // 노드 방문 -> 왼쪽 노드 이동 -> 오른쪽 노드 이동
    printf("%d ", node->data);
    _preorder(node->left);
    _preorder(node->right);
    printf("\n");
    printf("%d\n", temp);
}

void preorder(Tree * tree) {
    printf("preorder: ");
    _preorder(tree->root);
}

void bstDisplay(Tree * tree) {
    int start[10][10];
    preorder(tree);


}
