#include "parser.h"

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Usage: ./main filename\n");
        return 0;
    }
    
    printf("Compiling %s\n",argv[1]);
    parse(argv[1]);

    return 0;
}
