#include "parser.h"

void openFile(char* fname) {
    fp = fopen(fname,"r");
    if(fp == NULL) {
        perror("File failed to open");
        exit(1);
    }
}

void parse(char* fname) {
    char varName[MAX_CHARS];
    lineNumber = 1;
    currentR = 0;
    numUsed = 0;
    initSymTable();
    openFile(fname);
    lookahead = lexan();
    match(BEGIN);

    if(lookahead == INT) {
        varDeclaration();
    }

    while(lookahead == 300) {
        strcpy(varName,idLexeme);
        assignStmt();
        printf("%s = R0\n",varName);
        printPostFix();
        strcpy(postfix,"\0");
        currentR = 0;
    } 

    end();
    printf("\nSuccess.\n");
}

void varDeclaration() {
    while(lookahead == INT) {
        match(INT);
        if(lookahead != ID) {
            printf("Error on line %d: invalid declaration (expected an identifier)\n",lineNumber);
            exit(1);
        } 
        else {
            int loc = search(table,idLexeme);
            if(loc == NOT_FOUND) {
                insert(table,idLexeme,ID);
            }
            else {
                //redefinition error
                printf("Error on line %d: illegal redefinition %s\n",lineNumber,idLexeme);
                exit(1);
            }
            match(ID);
            while(lookahead == ',') {
                match(',');
                if(lookahead != ID) {
                    printf("Error on line %d: invalid declaration (expected an identifier after ',')\n",lineNumber);
                    exit(1);
                } 
                loc = search(table,idLexeme);
                if(loc == NOT_FOUND) {
                    insert(table,idLexeme,ID);
                }
                else {
                    //redefinition error
                    printf("Error on line %d: illegal redefinition %s\n",lineNumber,idLexeme);
                    exit(1);
                }
                match(ID);
            }
        }
        match(';');
    }
}

void end() {
    match(END);
    if(lookahead != '.') {
        printf("Error on Line %d: missing '.' (expected dot after end)\n",lineNumber);
        exit(1);
    }
    else {
        match(lookahead);
        match(DONE);
    }
}

void assignStmt() {
    int loc = search(table,idLexeme);
    if(loc == NOT_FOUND) {
        printf("Error on line %d: undefined variable %s\n",lineNumber,idLexeme);
        exit(1);
    }

    match(ID);
    if(lookahead != '=') {
        printf("Error on Line %d: missing '=' (expected assignment operator)\n",lineNumber);
        exit(1);
    }
    else {
        match(lookahead);
        expression();
        match(';');
    }
}

void expression() {
    char opcode[2];
    opcode[1] = '\0';
    term();
    while(lookahead == '+' || lookahead == '-') {
        opcode[0] = lookahead;
        match(lookahead);
        term();
        strcat(postfix,opcode);
        strcat(postfix,",");
        printf("R%d = R%d %s R%d\n",currentR-2,currentR-2,opcode,currentR-1);
        currentR--;
    }
}

void term() {
    char opcode[2];
    opcode[1] = '\0';
    factor();
    while(lookahead == '*' || lookahead == '/') {
        opcode[0] = lookahead;
        match(lookahead);
        factor();
        strcat(postfix,opcode);
        strcat(postfix,",");
        printf("R%d = R%d %s R%d\n",currentR-2,currentR-2,opcode,currentR-1);
        currentR--;
    }
}

void factor() {
    char operand[MAX_CHARS];
    if(lookahead == ID) {
        int loc = search(table,idLexeme);
        if(loc == NOT_FOUND) {
            printf("Error on line %d: undefined variable %s\n",lineNumber,idLexeme);
            exit(1);
        }
        strcpy(operand,idLexeme);
        strcat(postfix,operand);
        strcat(postfix,",");
        printf("R%d = %s\n",currentR,operand);
        match(ID);
        currentR++;
    }
    else if(lookahead == NUM) {
        strcpy(operand,numLexeme);
        strcat(postfix,operand);
        strcat(postfix,",");
        printf("R%d = %s\n",currentR,operand);
        match(NUM);
        currentR++;
    }
    else if(lookahead == '(') {
        match('(');
        expression();
        match(')');
    }
    else {
        printf("Error on Line %d: missing factor (expected an ID, NUM, or '(')\n",lineNumber);
        exit(1);
    }
}

void match(int t) {
    if(lookahead == t) {
        lookahead = lexan();
    }
    else {
        switch(t) {
            case 400:
                printf("Error on Line %d: syntax error (expected begin)\n",lineNumber);
                break;
            case 401:
                printf("Error on Line %d: syntax error (expected end.)\n",lineNumber);
                break;
            case 300:
                printf("Error on Line %d: syntax error (expected an identifier)\n",lineNumber);
                break;
            case 301:
                printf("Error on Line %d: syntax error (expected a number)\n",lineNumber);
                break;
            case 302:
                printf("Error on Line %d: syntax error (expected a type)\n",lineNumber);
                break;
            default: 
                printf("Error on Line %d: syntax error (expected a '%c')\n",lineNumber,(char)t);
        }
        exit(1);
    }
}

void printPostFix() {
    printf("*****[");
    *(strrchr(postfix,',')) = 0;
    printf("%s",postfix);
    printf("]*****\n");
}
