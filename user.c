#include <stdio.h>
#include "HashMap/library_HashMap.h"
#include <stdlib.h>
#include <string.h>

//key:이름, value:person
typedef struct Person{
    char name [32];
    int age;
}Person;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-signed-bitwise"
int hashCodeForString(void *data) {

    char * str = data;
    if(str == NULL){
        return -1;
    }
    int hash = 401;

    while (*str != '\0') {
        hash = ((hash << 4) + (int) (*str));
        str++;
    }
    return hash;
}
#pragma clang diagnostic pop

int equalsForVoid(void * key1, void * key2){
    if(key1 == NULL || key2 == NULL){
        return -1;
    }
    if(strcmp((const char*)key1, (const char*)key2) == 0){
        return 0;
    }
    return -1;
}

char * toStringForPerson(void * data){
    static char buf[1024];
    Person * person = data;
    sprintf(buf, "%s(%d)", person->name, person->age);
    return buf;
}

void increaseAge(void * key, void* value){
    if(key == NULL || value == NULL){
        return;
    }

    Person * person = value;
    ++person->age;
}

int main() {
    Person people[4] = {
            {"daniel", 20}, {"susan", 30}, {"petty", 40}, {"eddy", 50}
    };
    HashMap* map = initializeHashMap(toStringForPerson, equalsForVoid, hashCodeForString, 1);
    for (int i = 0; i < 4; i++)
        insertIntoHashMap(map, people[i].name, &people[i]);

    // 아래의 hashmapGet 함수를 구현해 보세요 :D
    for (int i = 0; i < 4; i++) {
        Person* p = hashMapGet(map, people[i].name);
        if (p)
            printf("key: %s, value: %d\n", people[i].name, p->age);
    }
    hashMapDisplay(map);

    hashMapForEach(map, increaseAge);
    hashMapDisplay(map);

    for (int i = 0; i < 4; i++) {
        hashMapRemove(map, people[i].name);
        hashMapDisplay(map);
    }
    finalizeHashMap(map);
    return 0;
}