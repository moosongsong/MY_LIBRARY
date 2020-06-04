#ifndef MY_LIBRARY_LIBRARY_HASHMAP_H
#define MY_LIBRARY_LIBRARY_HASHMAP_H

typedef int errno_t;

typedef char *(*DisplayFunction)(void *);

typedef int(*CompareFunction)(void *, void *);

typedef int(*HashCode)(void *key);

typedef void(*ExtraFunction)(void *key, void *value);

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
    DisplayFunction displayFunction;
    CompareFunction compareFunction;
    HashCode hashCode;
} HashMap;

static errno_t hashKey(HashMap *hashMap, void *key);

HashMap *initializeHashMap(DisplayFunction displayFunction, CompareFunction compareFunction, HashCode hashCode,
                           size_t bucketSize);

errno_t finalizeHashMap(HashMap *hashMap);

static Node *makeNode(void *key, void *value, int hash);

void *hashMapGet(HashMap *hashMap, void *key);

errno_t insertIntoHashMap(HashMap *hashMap, void *key, void *value);

void hashMapDisplay(HashMap *hashMap);

void* hashMapRemove(HashMap * hashMap, void * key);

int hashMapForEach(HashMap * hashMap, ExtraFunction extraFunction);

#endif //MY_LIBRARY_LIBRARY_HASHMAP_H
