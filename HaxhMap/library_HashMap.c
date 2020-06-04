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
//    FreeFunction freeFunctionForKey;
//    FreeFunction freeFunctionForValue;
    DisplayFunction displayFunction;
    CompareFunction compareFunction;
    HashCode hashCode;
} HashMap;

/*initialize hash map, return is hashMap*/
HashMap *initializeHashMap(DisplayFunction displayFunction,
                           CompareFunction compareFunction, HashCode hashCode, size_t bucketSize) {
//    if (freeFunctionForKey == NULL || displayFunction == NULL || compareFunction == NULL || freeFunctionForValue == NULL) {
//        fprintf(stderr, "function is empty");
//        return NULL;
//    }
    if (displayFunction == NULL || compareFunction == NULL) {
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
//    hashMap->freeFunctionForKey = freeFunctionForKey;
//    hashMap->freeFunctionForValue = freeFunctionForValue;
    hashMap->hashCode = hashCode;
    return hashMap;
}

/*to destory hash map*/
errno_t finalizeHashMap(HashMap *hashMap) {
    if (hashMap == NULL) {
        return -1;
    }

//    for (int i = 0; i < hashMap->bucketSize; ++i) {
//        for (Node *node = hashMap->buckets[i]; node != NULL;) {
//            hashMap->freeFunctionForKey(node->key);
//            hashMap->freeFunctionForValue(node->value);

//            Node *temp = node;
//            node = node->next;
//
            free(hashMap->buckets);
//        }
//    }

//    free(hashMap->buckets);
    free(hashMap);
}

/*make Node which is used for insert into Hash map function*/
static Node * makeNode(void * key, void * value, int hash){
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
    node->hash=hash;

    return node;
}

/*Function to change any key to an integer*/
static errno_t hashKey(HashMap * hashMap, void * key){
    int hashCode = hashMap->hashCode(key);

    hashCode += ~(hashCode << 9);
    hashCode ^= (((unsigned int)hashCode) >> 14);
    hashCode += (hashCode << 4);
    hashCode ^= (((unsigned int)hashCode) >> 10);
    return hashCode;
}

/*Index to hash value*/
static size_t calculateIndex(size_t bucketSize, int hash){
    return ((size_t)hash) & (bucketSize-1);
}

/*if 2 arguments are equals, return is 0*/
static errno_t equalsKey(void * key1, int hash1, void * key2, int hash2, CompareFunction compareFunction){
    if(key1 == NULL || key2 == NULL || compareFunction == NULL){
        return -1;
    }

    if(key1 == key2){
        return 0;
    }

    if(hash1 != hash2){
        return -1;
    }

    return compareFunction(key1, key2);
}

/*insert Node into hashMap*/
errno_t insertIntoHashMap(HashMap *hashMap, void *key, void *value) {
    if (hashMap == NULL || key == NULL || value == NULL) {
        perror("argument is null");
        return -1;
    }
    int hash = hashKey(hashMap, key);
    int index = calculateIndex(hashMap->bucketSize, hash);

    Node** ptr = &(hashMap->buckets[index]);

    while (20130613) {
        Node* cur = *ptr;
        int hash = hashKey(hashMap, key);
        if(cur == NULL){/*If there is no data for the key*/
            Node * node = makeNode(key, value, hash);
            if (node == NULL) {
                fprintf(stderr, "insertIntoHashMap: makeNode error\n");
                return -1;
            }

            *ptr = node;
            hashMap->count++;
            return 0;
        }

        if(equalsKey(cur->key, cur->hash, key, hash, hashMap->compareFunction) == 0){/*If there is data for the key*/
//            hashMap->freeFunctionForKey(cur->key);
//            hashMap->freeFunctionForValue(cur->value);
            cur->value=value;
            return 0;
        }
        ptr = &(cur->next);
    }
    return 0;
}

void hashMapDisplay(HashMap * hashMap){
    if(hashMap == NULL){
        return;
    }
    for (int i = 0; i < hashMap->bucketSize; ++i) {
        printf("bucket[%2lu]", i);
        for (Node* cur = hashMap->buckets[i]; cur != NULL; cur = cur->next)
            printf("->[%s]", hashMap->displayFunction(cur->value));
        printf("\n");
    }
}

void * hashMapGet(HashMap * hashMap, void * key){
    if(hashMap == NULL || key ==NULL){
        fprintf(stderr, "hashMapGet:argument is null");
        return NULL;
    }

    int hash = hashKey(hashMap, key);
    int index = calculateIndex(hashMap->bucketSize, hash);

    for (Node * node = hashMap->buckets[index]; node != NULL ; node = node->next) {
        if(hashMap->compareFunction(node->key, key) == 0){
            return node->value;
        }
    }
    return NULL;
}

int hashMapRemove(HashMap * hashMap, void * key){
    if (hashMap == NULL || key == NULL) {
        fprintf(stderr, "hashMapRemove: argument is null\n");
        return -1;
    }

    int hash = hashKey(hashMap, key);
    int index = calculateIndex(hashMap->bucketSize, hash);

    Node * node = hashMap->buckets[index];
    Node * prev = NULL;

    while (node != NULL){
        if(hashMap->compareFunction(node->key, key) ==0){
            prev->next = node->next;
            free(node);
            return 0;
        }
        prev=node;
        node=node->next;
    }

    return -1;
}