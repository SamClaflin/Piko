#include <stdio.h>
#include <stdlib.h>
#include "lexer/include/lexer.h"
#include "lexer/include/token.h"

int main(int argc, const char* argv[]) {
    LEXER lexer = lexer_createLexer();

    const char filename[] = "input.txt";
    FILE* inFile = fopen(filename, "r");
    if (!inFile) {
        printf("Could not open file '%s'\n", filename);
        exit(1);
    }

    lexer_readFile(lexer, inFile);
    lexer_printTokens(lexer);

    fclose(inFile);

    lexer_destroyLexer(&lexer);

    return 0;
}
