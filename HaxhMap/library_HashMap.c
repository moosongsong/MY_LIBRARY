#include <stdio.h>
#include <stdlib.h>
#include "library_HashMap.h"

typedef struct Node{
    const char * key;
    void * value;
    struct Node * next;
}Node;

typedef struct HashMap{
    Node ** buckets;
    size_t bucketSize;
    size_t count;
    FreeFunction freeFunction;
    DisplayFunction displayFunction;
    CompareFunction compareFunction;
}HashMap;

HashMap * initailizeHashMap(FreeFunction freeFunction, DisplayFunction displayFunction,
        CompareFunction compareFunction, size_t bucketSize){
    if(freeFunction == NULL || displayFunction == NULL || compareFunction == NULL){
        perror("function is empty");
        return NULL;
    }

    if(bucketSize == 0){
        perror("bucketSize is 0");
        return NULL;
    }

    Node ** buckets = calloc(bucketSize, sizeof(Node*));
    if(buckets == NULL){
        perror("bucket allocation is failed");
        return NULL;
    }

    HashMap * hashMap = calloc(1, sizeof(HashMap));
    if(hashMap == NULL){
        free(buckets);
        perror("map allocation is failed");
        return NULL;
    }

    hashMap->buckets=buckets;
    hashMap->bucketSize=bucketSize;
    hashMap->compareFunction=compareFunction;
    hashMap->displayFunction=displayFunction;
    hashMap->freeFunction=freeFunction;
//    hashMap->count=0;
    return hashMap;
}

errno_t finalizeHashMap(HashMap * hashMap){
    if(hashMap == NULL){
        perror("argument is null");
        return -1;
    }

    for (int i = 0; i < hashMap->bucketSize; ++i) {
        for (Node * node = hashMap->buckets[i]; node !=NULL ; node=node->next) {
            hashMap->freeFunction(node->value);
        }
        free(hashMap->buckets[i]);
    }

    free(hashMap->buckets);
    free(hashMap);
}