//
// Created by songe on 2020-06-02.
//

#ifndef MY_LIBRARY_LIBRARY_HASHMAP_H
#define MY_LIBRARY_LIBRARY_HASHMAP_H
typedef int errno_t ;
typedef void(*FreeFunction)(void*);
typedef char*(*DisplayFunction)(void*);
typedef int(*CompareFunction)(void*, void*);
typedef struct HashMap HashMap;
typedef struct Node Node;

HashMap * initailizeHashMap(FreeFunction freeFunction, DisplayFunction displayFunction,
                            CompareFunction compareFunction, size_t bucketSize);
errno_t finalizeHashMap(HashMap * hashMap);


#endif //MY_LIBRARY_LIBRARY_HASHMAP_H
