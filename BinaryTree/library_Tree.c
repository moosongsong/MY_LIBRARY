#include "library_Tree.h"
#include <stdio.h>
#include <stdlib.h>

errno_t bstInsert(Tree * tree, int data){
    Node * node = calloc(1, sizeof(Node));
    node->data = data;

    Node * root = tree->root;
    if(root == NULL){
        root = node;
        return 0;
    }

    while (20130613){
        if(root->data == data){
            return -1;
        }
        if(root->data > data){
            root= root->left;
        }else{
            root = root->right;
        }
        if(root == NULL){
            root = node;
            return 0;
        }
    }
}