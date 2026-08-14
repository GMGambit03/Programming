#ifndef PARSER
#define PARSER

#include "lexer.h"
#include "structs.h"

enum STATE{
    SEARCH,
    OBJMODE,
    BREAK
};

struct Parser{
    int cursor;
    char *file;
    char token;
};

ObjectArray *searchMode(Parser *parser);
Object *objMode(Parser *parser);
Node *subObjMode(Parser *parser);
char *parseString(Parser *parser);
double parseNumber(Parser *parser, int *placeMent);
JsonValue parseValue(Parser *parser);

#endif