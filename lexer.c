#include "lexer.h"

void initSymTable() {
    insert(table,"begin",BEGIN);
    insert(table,"end",END);
    insert(table,"int",INT);
}

int lexan() {
    char currChar;
    while(true) {
        currChar = fgetc(fp);
        if(isblank(currChar)) {
            //Do Nothing
        }
        else if(currChar == '\n') {
            //Increment line number
            lineNumber++;
        }
        else if(currChar == '~') {
            //Remove comment
            do {
                currChar = fgetc(fp);
            }while(currChar != '\n');
            ungetc(currChar,fp);
        }
        else if(isdigit(currChar)) {
            //Get the number into numLexeme
            int currIndex = 0;
            do {
                numLexeme[currIndex++] = currChar;
                currChar = fgetc(fp);
            }while(isdigit(currChar));
            numLexeme[currIndex] = '\0';
            ungetc(currChar,fp);
            return NUM;
        }
        else if(isalpha(currChar)) {
            //Get the identifier into idLexeme
            int currIndex = 0;
            do {
                idLexeme[currIndex++] = currChar;
                currChar = fgetc(fp);

                if(currChar == '_') {
                    idLexeme[currIndex++] = currChar;
                    currChar = fgetc(fp);
                    if(currChar == '_') {
                        printf("Error on line %d: illegal tokens '__' in identifier\n",lineNumber);
                        exit(1);
                    }
                    else if(!isalnum(currChar)) {
                        printf("Error on line %d: illegal identifier (can't end with '_')\n",lineNumber);
                        exit(1);
                    }
                }
            }while(isalnum(currChar));
            idLexeme[currIndex] = '\0';
            
            ungetc(currChar,fp);

            int loc = search(table,idLexeme);
            if(loc == NOT_FOUND) {
                return ID;
            }
            else {
                return table[loc].type;
            }
        }
        else if(currChar == EOF) {
            return DONE;
        }
        else {
            return currChar;
        }
    }
}
