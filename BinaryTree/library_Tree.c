#include "library_Tree.h"
#include <stdio.h>
#include <stdlib.h>

errno_t bstInsert(Tree * tree, int data){
    Node * node = calloc(1, sizeof(Node));

    Node * root = tree->root;
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