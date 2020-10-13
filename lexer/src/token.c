#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/token.h"

const int IDENTIFIER_SIZE_DEFAULT = 10;
const char TOKEN_TABLE[][2] = {
    // Alphabetic
    {'a', 1},
    {'b', 1},
    {'c', 1},
    {'d', 1},
    {'e', 1},
    {'f', 1},
    {'g', 1},
    {'h', 1},
    {'i', 1},
    {'j', 1},
    {'k', 1},
    {'l', 1},
    {'m', 1},
    {'n', 1},
    {'o', 1},
    {'p', 1},
    {'q', 1},
    {'r', 1},
    {'s', 1},
    {'t', 1},
    {'u', 1},
    {'v', 1},
    {'w', 1},
    {'x', 1},
    {'y', 1},
    {'z', 1},
    {'A', 1},
    {'B', 1},
    {'C', 1},
    {'D', 1},
    {'E', 1},
    {'F', 1},
    {'G', 1},
    {'H', 1},
    {'I', 1},
    {'J', 1},
    {'K', 1},
    {'L', 1},
    {'M', 1},
    {'N', 1},
    {'O', 1},
    {'P', 1},
    {'Q', 1},
    {'R', 1},
    {'S', 1},
    {'T', 1},
    {'U', 1},
    {'V', 1},
    {'W', 1},
    {'X', 1},
    {'Y', 1},
    {'Z', 1},

    // Delims
    {'(', 2},
    {')', 2},
    {'[', 2},
    {']', 2},
    {'{', 2},
    {'}', 2},
    {',', 2},
    {';', 2},
    {'"', 2},
    {'\'', 2},
    {'\\', 2},

    // Operators
    {'=', OPERATOR_TYPE},
    {'+', OPERATOR_TYPE},
    {'-', OPERATOR_TYPE},
    {'/', OPERATOR_TYPE},
    {'*', OPERATOR_TYPE},
    {'.', OPERATOR_TYPE},
    {'!', OPERATOR_TYPE},
    {'>', OPERATOR_TYPE},
    {'<', OPERATOR_TYPE},
    {'&', OPERATOR_TYPE},
    {'|', OPERATOR_TYPE},
    {'%', OPERATOR_TYPE},

    // Whitespace 
    {' ', 4},
    {'\t', 4},
    {'\n', 4},
    {'\r', 4},
    {'\v', 4},
    {'\f', 4},

    // Numbers
    {'0', 5},
    {'1', 5},
    {'2', 5},
    {'3', 5},
    {'4', 5},
    {'5', 5},
    {'6', 5},
    {'7', 5},
    {'8', 5},
    {'9', 5},

    // End of Table
    {'\0', 0}
};

typedef struct {
    char* identifier;
    int type;
    int capacity;
    int size;
} Token;


TOKEN token_createToken() {
    Token* newToken = (Token*)malloc(sizeof(Token));
    if (!newToken) { return NULL; }

    newToken->identifier = (char*)malloc(sizeof(char) * IDENTIFIER_SIZE_DEFAULT);
    if (!newToken->identifier) { return NULL; }

    newToken->capacity = IDENTIFIER_SIZE_DEFAULT;
    newToken->type = 0;
    newToken->size = 0;

    return (TOKEN)newToken;
}

void token_destroyToken(TOKEN* phToken) {
    if (!phToken) { return; }

    Token* pToken = (Token*)*phToken;

    free(pToken->identifier);
    free(*phToken);
    *phToken = NULL;
}

void token_printContents(TOKEN hToken) {
    if (!hToken) { return; }

    Token* pToken = (Token*)hToken;

    for (int i = 0; i < pToken->size; ++i) {
        printf("%c", pToken->identifier[i]);
    }
    printf("\t\t%d\n", pToken->type);
}

void token_pushChar(TOKEN hToken, char currChar) {
    if (!hToken) { return; }

    Token* pToken = (Token*)hToken;

    if (pToken->size == pToken->capacity - 1) {
        int newCapacity = pToken->capacity * 2;
        char* newIdentifier = (char*)malloc(sizeof(char) * newCapacity);
        if (!newIdentifier) { return; }

        for (int i = 0; i < pToken->size; ++i) {
            newIdentifier[i] = pToken->identifier[i];
        }

        free(pToken->identifier);
        pToken->identifier = newIdentifier;
        pToken->capacity = newCapacity;
    }

    ++pToken->size;
    pToken->identifier[pToken->size - 1] = currChar;
    pToken->type = token_getCharType(currChar);
}

char token_popChar(TOKEN hToken) {
    if (!hToken) { return -1; }

    Token* pToken = (Token*)hToken;

    if (pToken->size == 0) {
        return -1;
    }

    char returnChar = pToken->identifier[pToken->size - 1];
    pToken->identifier[pToken->size -1] = 0;
    --pToken->size;

    return returnChar;
}

int token_getType(TOKEN hToken) {
    if (!hToken) { return -1; }

    Token* pToken = (Token*)hToken;

    return pToken->type;
}

int token_getSize(TOKEN hToken) {
    if (!hToken) { return -1; }

    Token* pToken = (Token*)hToken;

    return pToken->size;
}

int token_getCapacity(TOKEN hToken) {
    if (!hToken) { return -1; }

    Token* pToken = (Token*)hToken;

    return pToken->capacity;
}

char* token_getIdentifier(TOKEN hToken) {
    if (!hToken) { return 0; }

    Token* pToken = (Token*)hToken;

    return pToken->identifier;
}

int token_getCharType(const char currChar) {
    int i = 0;
    while (TOKEN_TABLE[i][0] != '\0') {
        if (currChar == TOKEN_TABLE[i][0]) {
            return TOKEN_TABLE[i][1];
        }

        ++i;
    }

    return -1;
}

int token_compare(TOKEN hToken, const char string[]) {
    if (!hToken) { return -1; }

    Token* pToken = (Token*)hToken;

    if (pToken->size != strlen(string)) {
        return 0;
    }

    for (int i = 0; i < pToken->size; ++i) {
        if (string[i] != '\0' && pToken->identifier[i] != string[i]) {
            return 0;
        }
    }

    return 1;
}
