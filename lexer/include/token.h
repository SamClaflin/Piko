#pragma once 

typedef void* TOKEN;

TOKEN token_createToken();
void token_destroyToken(TOKEN* phToken);
void token_printContents(TOKEN hToken);
void token_pushChar(TOKEN hToken, char currChar);
char token_popChar(TOKEN hToken);
int token_getType(TOKEN hToken);
int token_getSize(TOKEN hToken);
int token_getCapacity(TOKEN hToken);
char* token_getIdentifier(TOKEN hToken);
int token_getCharType(const char currChar);
