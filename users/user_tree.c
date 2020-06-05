//#include "../BinaryTree/library_Tree.h"
//#include <stdio.h>
//#include <stdlib.h>
//
//int main() {
//    Tree * tree = calloc(1, sizeof(Tree));
//    int arr[8] = { 4, 2, 1, 3, 6, 5, 7, 8 };
//    for (int i = 0; i < 8; i++){
//        bstInsert(tree, arr[i]);
//    }
//    bstDisplay(tree);
//}


#include <stdlib.h>
#include <stdio.h>

// 이진 검색 트리(BST)
typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;
Node *root;

int bstInsert(int data) {
    Node *node = calloc(1, sizeof(Node));
    if (node == NULL) {
        perror("bstInsert");
        return -1;
    }
    node->data = data;
    if (root == NULL) {    // 트리가 비어 있는 경우
        root = node;
        return 0;
    }
    Node *parent = NULL;
    Node *cur = root;
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

static void fillArray(int(*arr)[10], int *row, int *col, Node *node) {
    if (node == NULL) {
        return;
    }

    ++(*row);
    fillArray(arr, row, col, node->left);
    arr[*row][(*col)++] = node->data;
    fillArray(arr, row, col, node->right);
    --(*row);
}

void bstDisplay() {
    int arr[10][10] = {0};
    int row = -1;
    int col = 0;

//    system("cls");
    fillArray(arr, &row, &col, root);

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (arr[i][j]) {
                printf("(%2d)", arr[i][j]);
            } else {
                printf("%4c", ' ');
            }
        }
        printf("\n");
    }
}


int bstGet(int key) {
    if (root == NULL)
        return -1;

    Node *cur = root;
    while (cur != NULL) {
        if (key < cur->data)
            cur = cur->left;
        else if (key > cur->data)
            cur = cur->right;
        else
            return cur->data;
    }
    return -1;
}


int bstDelete(int data) {
    if (root == NULL) {
        return -1;
    }
    Node *prev = NULL;
    Node *node = root;

    while (node != NULL && node->data != data) {
        prev = node;
        if (data < node->data) {
            node = node->left;
        } else if (data < node->data) {
            node = node->right;
        }
    }

    if (node == NULL) {
        return -1;
    }
    
    if (node->right == NULL && node == NULL) {
        prev->right == NULL;
        prev->left == NULL;
        free(node);
        return 0;
    } else if (node->right == NULL || node->left == NULL) {
        if (node == prev->left) {
            if (node->left != NULL) {
                prev->left = node->left;
            } else {
                prev->left = node->right;
            }
        } else {
            if (node->left != NULL) {
                prev->right = node->left;
            } else {
                prev->right = node->right;
            }
        }
    } else {

    }
}

}

int main() {
    int arr[8] = {4, 2, 1, 3, 6, 5, 7, 8};
    for (int i = 0; i < 8; i++) {
        bstInsert(arr[i]);
    }
    bstDisplay();

    for (int j = 0; j < 8; ++j) {
        int data = bstGet(j + 1);
        printf("%d\n", data);
    }
}