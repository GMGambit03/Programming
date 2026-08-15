#ifndef PARSER
#define PARSER

#include "lexer.h"
#include "structs.h"

enum STATE{
    SEARCH,
    OBJMODE,
    BREAK
};

typedef struct{
    int prev;
    int cursor;
    char *file;
    char token;
}Parser;

ObjectArray *searchMode(Parser *parser);
Object *objMode(Parser *parser);
Node *subObjMode(Parser *parser);
char *parseString(Parser *parser);
double parseNumber(Parser *parser, int *placeMent);
JsonValue parseValue(Parser *parser);
JsonArray *arrayMode(Parser *parser);
int getStrArrCnt(Parser *parser);

#endif