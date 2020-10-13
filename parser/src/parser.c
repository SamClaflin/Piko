#include <stdio.h>
#include <stdlib.h>
#include "../include/parser.h"

int parser_getOperatorPrecedence(TOKEN hToken) {
    if (!hToken) { return -1; }

    // Precedence 1 
    if (token_compare(hToken, "++") == 1) { return 1; }
    if (token_compare(hToken, "--") == 1) { return 1; }

    // Precedence 2
    if (token_compare(hToken, "!") == 1) { return 2; }

    // Precedence 3
    if (token_compare(hToken, "*") == 1) { return 3; }
    if (token_compare(hToken, "/") == 1) { return 3; }
    if (token_compare(hToken, "%") == 1) { return 3; }

    // Precedence 4
    if (token_compare(hToken, "+") == 1) { return 4; }
    if (token_compare(hToken, "-") == 1) { return 4; }

    // Precedence 5
    if (token_compare(hToken, "<") == 1) { return 5; }
    if (token_compare(hToken, ">") == 1) { return 5; }
    if (token_compare(hToken, "<=") == 1) { return 5; }
    if (token_compare(hToken, ">=") == 1) { return 5; }

    // Precedence 6
    if (token_compare(hToken, "==") == 1) { return 6; }
    if (token_compare(hToken, "!=") == 1) { return 6; }

    // Precedence 7
    if (token_compare(hToken, "&&") == 1) { return 7; }

    // Precedence 8
    if (token_compare(hToken, "||") == 1) { return 8; }
    
    // Precedence 9
    if (token_compare(hToken, "=") == 1) { return 9; }
    if (token_compare(hToken, "+=") == 1) { return 9; }
    if (token_compare(hToken, "-=") == 1) { return 9; }
    if (token_compare(hToken, "*=") == 1) { return 9; }
    if (token_compare(hToken, "/=") == 1) { return 9; }
    if (token_compare(hToken, "%=") == 1) { return 9; }

    return -1;
}

TOKEN parser_getLowestPrecedence(LEXER hLexer) {
    if (!hLexer) { return NULL; }

    TOKEN* tokenArr = lexer_getTokenArray(hLexer);
    if (!tokenArr) { return NULL; }

    int numTokens = lexer_getNumTokens(hLexer);

    TOKEN lowestPrec = tokenArr[0];
    for (int i = 1; i < numTokens; ++i) {
        if (token_getType(tokenArr[i]) == OPERATOR_TYPE) {
            if (parser_getOperatorPrecedence(lowestPrec) < parser_getOperatorPrecedence(tokenArr[i])) {
                lowestPrec = tokenArr[i];
            }
        }    
    }

    return lowestPrec;
}
