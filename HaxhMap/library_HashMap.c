#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library_HashMap.h"

typedef struct Node {
    void *key;
    void *value;
    int hash;
    struct Node *next;
} Node;

typedef struct HashMap {
    Node **buckets;
    size_t bucketSize;
    size_t count;
    FreeFunction freeFunctionForKey;
    FreeFunction freeFunctionForValue;
    DisplayFunction displayFunction;
    CompareFunction compareFunction;
    HashCode hashCode;
} HashMap;

HashMap *initailizeHashMap(FreeFunction freeFunctionForKey, FreeFunction freeFunctionForValue, DisplayFunction displayFunction,
                           CompareFunction compareFunction, HashCode hashCode, size_t bucketSize) {
    if (freeFunctionForKey == NULL || displayFunction == NULL || compareFunction == NULL || freeFunctionForValue == NULL) {
        fprintf(stderr, "function is empty");
        return NULL;
    }

    if (bucketSize == 0) {
        fprintf(stderr, "bucketSize is 0");
        return NULL;
    }

    Node **buckets = calloc(bucketSize, sizeof(Node *));
    if (buckets == NULL) {
        perror("bucket allocation is failed");
        return NULL;
    }

    HashMap *hashMap = calloc(1, sizeof(HashMap));
    if (hashMap == NULL) {
        free(buckets);
        perror("map allocation is failed");
        return NULL;
    }

    hashMap->buckets = buckets;
    hashMap->bucketSize = bucketSize;
    hashMap->compareFunction = compareFunction;
    hashMap->displayFunction = displayFunction;
    hashMap->freeFunctionForKey = freeFunctionForKey;
    hashMap->freeFunctionForValue = freeFunctionForValue;
    hashMap->hashCode = hashCode;
    return hashMap;
}

errno_t finalizeHashMap(HashMap *hashMap) {
    if (hashMap == NULL) {
        fprintf(stderr, "map is empty.");
        return -1;
    }

    for (int i = 0; i < hashMap->bucketSize; ++i) {
        for (Node *node = hashMap->buckets[i]; node != NULL;) {
            hashMap->freeFunctionForKey(node->key);
            hashMap->freeFunctionForValue(node->value);

            Node *temp = node;
            node = node->next;

            free(temp);
        }
    }

    free(hashMap->buckets);
    free(hashMap);
}

static Node * makeNode(HashMap * hashMap, void * key, void * value){
    if (key == NULL || value == NULL) {
        fprintf(stderr, "makeNode: argument is null\n");
        return NULL;
    }

    Node* node = calloc(1, sizeof(Node));
    if (node == NULL) {
        perror("makeNode");
        return NULL;
    }

    node->key=key;
    node->value=value;
    node->hash=hashMap->hashCode(key, hashMap);
    return node;
}

errno_t insertIntoHashMap(HashMap *hashMap, void *key, void *value) {
    if (hashMap == NULL || key == NULL || value == NULL) {
        perror("argument is null");
        return -1;
    }

    int index = hashMap->hashCode(key, hashMap->bucketSize);
    Node** ptr = &(hashMap->buckets[index]);

    while (20130613) {
        Node* cur = *ptr;
        if(cur == NULL){
            Node * node = makeNode(hashMap, key, value);
            if (node == NULL) {
                fprintf(stderr, "insertIntoHashMap: makeNode error\n");
                return -1;
            }
            *ptr = node;
            hashMap->count++;
            return 0;
        }
        if(hashMap->compareFunction(cur->key, key) == 0){
            hashMap->freeFunctionForKey(cur->key);
            hashMap->freeFunctionForValue(cur->value);
            cur->key=key;
            return 0;
        }
        ptr = &(cur->next);

    }
}

void hashMapDisplay(HashMap * hashMap){
    if(hashMap == NULL){
        return;
    }
    for (int i = 0; i < hashMap->bucketSize; ++i) {
        printf("bucket[%2lu]", i);
        for (Node* cur = hashMap->buckets[i]; cur != NULL; cur = cur->next)
            printf("->[%s]", hashMap->displayFunction(cur));
        printf("\n");
    }
}

Node * hashMapGet(HashMap * hashMap, char * key){
    if(hashMap == NULL || key ==NULL){
        fprintf(stderr, "argument is null");
        return NULL;
    }

    int index = hashMap->hashCode(key, hashMap);
    for (Node * node = hashMap->buckets[index]; node != NULL ; node = node->next) {
        if(hashMap->compareFunction(node->key, key) ==0){
            return node;
        }
    }
    return NULL;
}

int hashMapRemove(HashMap * hashMap, void * key){
    if (hashMap == NULL || key == NULL) {
        fprintf(stderr, "hashMapRemove: argument is null\n");
        return -1;
    }

    int index = hashMap->hashCode(key, hashMap->bucketSize);
    for (Node * node = hashMap->buckets[index]; node != NULL ; node = node->next) {
        if(hashMap->compareFunction(node->key, key) ==0){
            node->next=
            hashMap->freeFunctionForKey(node->key);
            hashMap->freeFunctionForValue(node->value);
            free(node);
            return 0;
        }
    }
    return -1;
}