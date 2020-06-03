#include <stdio.h>
#include "HaxhMap/library_HashMap.h"

int hashCodeForString(const char *str, int bucketSize) {
    int hash = 401;
    int c;

    while (*str != '\0') {
        hash = ((hash << 4) + (int) (*str)) % bucketSize;
        str++;
    }
    return hash % (bucketSize);
}

int main(){
    return 0;
}