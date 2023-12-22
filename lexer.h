#ifndef LEXER_H
#define LEXER_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "symbol.h"

#define ID 300
#define NUM 301
#define INT 302
#define BEGIN 400
#define END 401
#define NOT_FOUND -1
#define DONE 0
#define MAX_CHARS 25

char idLexeme[MAX_CHARS];
char numLexeme[MAX_CHARS];

char postfix[50];

int lineNumber;

int lookahead;

int currentR;

FILE * fp;

void initSymTable();

/*
 * returns token type
 */
int lexan();

#endif
