#include "symbol.h"

void insert(symbol table[], char key[], int type) {
    //if not already in table, and table isn't full.
    if(search(table,key) == -1 && (numUsed < TABLE_SIZE)) {
        strcpy(table[numUsed].value,key);
        table[numUsed].type = type;
        numUsed++;
    }
}

void remo(symbol table[], char* key) {
    for(int i = 0; i < TABLE_SIZE; ++i) {
        if(table[i].value == key) {
            strcpy(table[i].value,"");
            table[i].type = -1;
            return;
        }
    }
}

int search(symbol table[], char key[]) {
    for(int i = 0; i < TABLE_SIZE; ++i) {
        if(table[i].value != NULL && strcmp(table[i].value,key) == 0)
            return i;
    }

    return -1;
}
