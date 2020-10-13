#pragma once 

#include "../include/token.h"

typedef void* LEXER;

LEXER lexer_createLexer();
void lexer_destroyLexer(LEXER* phLexer);
void lexer_printTokens(LEXER hLexer);
void lexer_pushChar(LEXER hLexer, char currChar);
void lexer_readFile(LEXER hLexer, FILE* inFile);
TOKEN* lexer_getTokenArray(LEXER hLexer);
int lexer_getNumTokens(LEXER hLexer);
int lexer_getCapacity(LEXER hLexer);
