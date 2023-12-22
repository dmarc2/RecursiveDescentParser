#ifndef PARSER_H
#define PARSER_H
#include <stdlib.h>
#include "lexer.h"

void parse(char* fname);
void match(int t);
void end();
void varDeclaration();
void assignStmt();
void expression();
void term();
void factor();
void printPostFix();

#endif
