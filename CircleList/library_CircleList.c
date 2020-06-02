#include "library_CircleList.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    void * data;
    struct Node * next;
    struct Node * prev;
}Node;

typedef struct List{
    Node * head;
    int count;
    FreeFunction freeFunction;
    DisplayFunction displayFunction;
    CompareFunction compareFunction;
};

List * initializeList(FreeFunction freeFunction,
        DisplayFunction displayFunction, CompareFunction compareFunction){
    if(freeFunction == NULL || displayFunction == NULL){
        perror("function is empty");
        return NULL;
    }

    List * list = calloc(1, sizeof(List));
    if(list == NULL){
        perror("list calloc failed");
        return NULL;
    }

    Node * head = calloc(1, sizeof(Node));
    if(head == NULL){
        perror("head calloc failed");
        free(list);
        return NULL;
    }

    list->head = head;
    list->count=0;
    list->freeFunction = freeFunction;
    list->displayFunction = displayFunction;
    list->compareFunction = compareFunction;
    return list;
}

errno_t finalizeList(List * list){
    if(list == NULL){
        perror("list is null");
        return -1;
    }
    Node * head = list->head;

    while(head->next != head){
        Node * node = head->next;
        head->next = node->next;
        node->next->prev = head;
        list->freeFunction(node->data);
        free(node);
    }
    free(head);
    free(list);
    return 0;
}

static void insertNodeIntoList(Node * new, Node * start){
    start->next->prev=new;
    new->next=start->next;
    start->next=new;
    new->prev=start;
}

errno_t insertListToFirst(List * list, void * data){
    if(list == NULL || data == NULL){
        perror("arguments are null");
        return -1;
    }

    Node * node = calloc(1, sizeof(Node));
    if (node == NULL){
        perror("node allocation failed");
        return -1;
    }
    insertNodeIntoList(node, list->head);
    return 0;
}

errno_t insertListToLast(List * list, void * data){
    if(list == NULL || data == NULL){
        perror("arguments are null");
        return -1;
    }

    Node * node = calloc(1, sizeof(Node));
    if (node == NULL){
        perror("node allocation failed");
        return -1;
    }
    insertNodeIntoList(node, list->head->prev);
    return 0;
}

void displayList(List * list){
    if(list == NULL){
        perror("argument is null");
        return; -1;
    }

    for (Node * node = list->head->next; node != list->head ; node = node->next) {
        printf("%s\n", list->displayFunction(node->data));
    }
}

Node * getNodeFromList(List * list, void * data){
    if(list == NULL || data == NULL){
        perror("argument is null");
        return NULL;
    }

    for (Node * node = list->head->next; node != list->head ; node = node->next) {
        int temp = list->compareFunction(data, node->data);
        if(temp == 0){
            return node;
        }
    }

    return NULL;
}

errno_t removeNodeFromList(List * list, void * data){
    if(list == NULL || data == NULL){
        perror("argument is null");
        return -1;
    }

    for (Node * node = list->head->next; node != list->head ; node = node->next) {
        int temp = list->compareFunction(data, node->data);
        if(temp == 0){
            node->prev->next=node->next;
            node->next->prev=node->prev;
            free(node->data);
            free(node);
            return 0;
        }
    }
}