#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library_HashMap.h"

typedef struct Node {
    char *key;
    void *value;
    struct Node *next;
} Node;

typedef struct HashMap {
    Node **buckets;
    size_t bucketSize;
    size_t count;
    FreeFunction freeFunction;
    DisplayFunction displayFunction;
    CompareFunction compareFunction;
    HashCode hashCode;
} HashMap;

HashMap *initailizeHashMap(FreeFunction freeFunction, DisplayFunction displayFunction,
                           CompareFunction compareFunction, HashCode hashCode, size_t bucketSize) {
    if (freeFunction == NULL || displayFunction == NULL || compareFunction == NULL) {
        perror("function is empty");
        return NULL;
    }

    if (bucketSize == 0) {
        perror("bucketSize is 0");
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
    hashMap->freeFunction = freeFunction;
    hashMap->hashCode = hashCode;
//    hashMap->count=0;
    return hashMap;
}

errno_t finalizeHashMap(HashMap *hashMap) {
    if (hashMap == NULL) {
        fprintf(stderr, "map is empty.");
        return -1;
    }

    for (int i = 0; i < hashMap->bucketSize; ++i) {
        for (Node *node = hashMap->buckets[i]; node != NULL;) {
            free(node->key);
            hashMap->freeFunction(node->value);

            Node *temp = node;
            node = node->next;

            free(node);
        }
    }

    free(hashMap->buckets);
    free(hashMap);
}

int hash(const char *str, HashMap *map) {
    int hash = 401;
    int c;

    while (*str != '\0') {
        hash = ((hash << 4) + (int) (*str)) % map->bucketSize;
        str++;
    }

    return hash % map->bucketSize;
}


errno_t insertIntoHashMap(HashMap *hashMap, char *key, void *value) {
    if (hashMap == NULL || key == NULL || value == NULL) {
        perror("argument is null");
        return -1;
    }

    int index = hashMap->hashCode(key);

    Node *node = hashMap->buckets[index];
    if (node == NULL) {
        Node *temp = calloc(1, sizeof(Node));
        if (temp == NULL) {
            perror("allocation is failed");
            return -1;
        }
        temp->key = key;
        temp->value = value;
        hashMap->buckets[index] = temp;
        hashMap->count++;
        return 0;
    }

    while (node) {

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
        fprintf(stderr, "atgument is null");
        return NULL;
    }

    int index = hashMap->hashCode(key);
    Node * temp = hashMap->buckets[index];
    for (Node * node = temp; node != NULL ; node = node->next) {
        if(strcmp(key, node->key)==0){
            return node;
        }
    }
    return NULL;
}

