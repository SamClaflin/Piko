#include <stdio.h>
#include <stdlib.h>
#include "../include/lexer.h"

const int TOKEN_CAPACITY_DEFAULT = 10;

typedef struct {
    TOKEN* tokenArr;
    int numTokens;
    int tokenCapacity;
} Lexer;

LEXER lexer_createLexer() {
    Lexer* newLexer = (Lexer*)malloc(sizeof(Lexer));
    if (!newLexer) { return NULL; }

    newLexer->tokenArr = (TOKEN*)malloc(sizeof(TOKEN) * TOKEN_CAPACITY_DEFAULT);
    if (!newLexer->tokenArr) { return NULL; }

    for (int i = 0; i < TOKEN_CAPACITY_DEFAULT; ++i) {
        newLexer->tokenArr[i] = token_createToken();
    }

    newLexer->numTokens = 1;
    newLexer->tokenCapacity = TOKEN_CAPACITY_DEFAULT;

    return newLexer;
}

void lexer_destroyLexer(LEXER* phLexer) {
    if (!phLexer) { return; }

    Lexer* pLexer = (Lexer*)*phLexer;

    for (int i = 0; i < pLexer->tokenCapacity; ++i) {
        token_destroyToken(&pLexer->tokenArr[i]);
    }

    free(pLexer->tokenArr);
    free(*phLexer);
    *phLexer = NULL;
}

void lexer_printTokens(LEXER hLexer) {
    if (!hLexer) { return; }

    Lexer* pLexer = (Lexer*)hLexer;

    for (int i = 0; i < pLexer->numTokens; ++i) {
        token_printContents(pLexer->tokenArr[i]);
    }
}

void lexer_pushChar(LEXER hLexer, char currChar) {
    if (!hLexer) { return; }

    Lexer* pLexer = (Lexer*)hLexer;

    int currTokenType = token_getType(pLexer->tokenArr[pLexer->numTokens - 1]);
    int currCharType = token_getCharType(currChar);

    if (currTokenType == currCharType) {
        token_pushChar(pLexer->tokenArr[pLexer->numTokens - 1], currChar);
    } else {
        if (pLexer->numTokens == pLexer->tokenCapacity - 1) {
            int newCapacity = pLexer->tokenCapacity * 2;
            TOKEN* newTokenArr = (TOKEN*)malloc(sizeof(TOKEN) * newCapacity);
            if (!newTokenArr) { return; }

            int i = 0; 
            while (i < pLexer->tokenCapacity) {
                newTokenArr[i] = pLexer->tokenArr[i];
                ++i;
            }
            while (i < newCapacity) {
                newTokenArr[i] = token_createToken();
                ++i;
            }

            free(pLexer->tokenArr);
            pLexer->tokenArr = newTokenArr;
            pLexer->tokenCapacity = newCapacity;
        }

        if (currTokenType != 0) {
            ++pLexer->numTokens;
        }

        token_pushChar(pLexer->tokenArr[pLexer->numTokens - 1], currChar);
    }
}

void lexer_readFile(LEXER hLexer, FILE* inFile) {
    if (!hLexer || !inFile) { return; }

    char currChar;
    while (1) {
        currChar = fgetc(inFile);
        if (currChar == EOF) { break; }

        lexer_pushChar(hLexer, currChar);
    }
}

TOKEN* lexer_getTokenArray(LEXER hLexer) {
    if (!hLexer) { return NULL; }

    Lexer* pLexer = (Lexer*)hLexer;

    return pLexer->tokenArr;
}

int lexer_getNumTokens(LEXER hLexer) {
    if (!hLexer) { return -1; }

    Lexer* pLexer = (Lexer*)hLexer;

    return pLexer->numTokens;
}

int lexer_getCapacity(LEXER hLexer) {
    if (!hLexer) { return -1; }

    Lexer* pLexer = (Lexer*)hLexer;

    return pLexer->tokenCapacity;
}
