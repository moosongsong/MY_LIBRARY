#include <stdio.h>
#include "HaxhMap/library_HashMap.h"
#include <stdlib.h>
#include <string.h>

//key:이름, value:person
typedef struct Person{
    char name [32];
    int age;
}Person;

int hashCodeForString(const char *str, int bucketSize) {
    if(str == NULL || bucketSize<0){
        return -1;
    }
    int hash = 401;
    int c;

    while (*str != '\0') {
        hash = ((hash << 4) + (int) (*str)) % bucketSize;
        str++;
    }
    return hash % (bucketSize);
}

int equalsForKeyName(void * key1, void * key2){

}

char * toStringForPerson(Person person){
    char * str = "";
    strcat(str, person.name);
    strcat(str,":");
    strcat(str, person.age);
    return str;
}

char * toStringForAddress(Address address){
    char * str ="";
    strcat(str, address.roadNum);
    strcat(str, ":");
    strcat(str, address.floor);
    strcat(str, ":");
    strcat(str, address.roomNum);
    return str;
}

int main(){
    char* names[5] = { "daniel", "susan", "andrew", "monica", "petty" };
    char* ages[5] = { "10", "20", "30", "40", "50" };

    HashMap * map = initailizeHashMap(NULL, NULL, toStringForAddress, NULL, hashCodeForString, 10);
    for (int i = 0; i < 5; i++) {
        char* oldValue;
        insertIntoHashMap(map, names[i], ages[i]);
    }
    hashMapDisplay(map);

    // 아래의 hashmapRemove 함수를 구현해 보세요 :D
    for (int i = 0; i < 5; i++) {
        const char* value = hashMapRemove(map, names[i]);
        free((void*)value);
        hashMapDisplay(map);
    }

    finalizeHashMap(map);
    return 0;
}