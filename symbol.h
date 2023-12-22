#ifndef SYMBOL_H
#define SYMBOL_H
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define TABLE_SIZE 25
#define KEY_LEN 25

typedef struct {
    char value[KEY_LEN];
    int type;
}symbol;

int numUsed;

symbol table[TABLE_SIZE];

/*
 * This function inserts a key value into the hash table under two 
 * conditions: The hash table isn't full, and if the key isn't already
 * in the table.
 * Precondition: Pass in a valid key string.
 * Postcondition: The key value is now in the hash table.
 */
void insert(symbol table[], char* key, int type);

/*
 * This function removes a key value from the hash table.
 * Precondition: Pass in a valid key string.
 * Postcondition: The key value has been removed from the hash table.
 */
void remo(symbol table[], char* key);

/*
 * This function is used to search the hash table for a key value.
 * Precondition: Pass in a valid key string.
 * Postcondition: If the key is in the list, the function will return its index;
 * otherwise, the function returns -1.
 */
int search(symbol table[], char* key);

#endif
