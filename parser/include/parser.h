#pragma once 

#include "../../lexer/include/token.h"
#include "../../lexer/include/lexer.h"

int parser_getOperatorPrecedence(TOKEN hToken);
TOKEN parser_getLowestPrecedence(LEXER hLexer);
