#ifndef MY_LIBRARY_LIBRARY_CIRCLELIST_H
#define MY_LIBRARY_LIBRARY_CIRCLELIST_H

typedef int errno_t;

typedef void(*FreeFunction)(void *);

typedef char *(*DisplayFunction)(void *);

typedef int(*CompareFunction)(void *, void *);

typedef struct Node Node;
typedef struct List List;

List *initializeList(FreeFunction freeFunction, DisplayFunction displayFunction, CompareFunction compareFunction);

errno_t finalizeList(List *list);

static void insertNodeIntoList(Node *new, Node *start);

errno_t insertListToFirst(List *list, void *data);

errno_t insertListToLast(List *list, void *data);

Node *getNodeFromList(List *list, void *data);

void displayList(List *list);

#endif //MY_LIBRARY_LIBRARY_CIRCLELIST_H