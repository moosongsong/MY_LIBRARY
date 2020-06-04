#ifndef MY_LIBRARY_LIBRARY_HASHMAP_H
#define MY_LIBRARY_LIBRARY_HASHMAP_H

typedef struct HashMap HashMap;
typedef struct Node Node;
typedef int errno_t;

typedef void(*FreeFunction)(void *);

typedef char *(*DisplayFunction)(void *);

typedef int(*CompareFunction)(void *, void *);

typedef int(*HashCode)(void *key);

static errno_t hashKey(HashMap *hashMap, void *key);

//HashMap *initializeHashMap(FreeFunction freeFunctionForKey, FreeFunction freeFunctionForValue, DisplayFunction displayFunction,
//                           CompareFunction compareFunction, HashCode hashCode, size_t bucketSize);

HashMap *initializeHashMap(DisplayFunction displayFunction, CompareFunction compareFunction, HashCode hashCode,
                           size_t bucketSize);

errno_t finalizeHashMap(HashMap *hashMap);

static Node *makeNode(void *key, void *value, int hash);

void *hashMapGet(HashMap *hashMap, void *key);

errno_t insertIntoHashMap(HashMap *hashMap, void *key, void *value);

void hashMapDisplay(HashMap *hashMap);

int hashMapRemove(HashMap *hashMap, void *key);

#endif //MY_LIBRARY_LIBRARY_HASHMAP_H
