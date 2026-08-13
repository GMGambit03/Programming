#include "Headers/parser.h"
#include "Headers/structs.h"
#include <stdlib.h>


ObjectArray *searchMode(Parser *parser){

    // Initialize search mode to start iterating through json file
    int state = SEARCH;
    // create the object that will be returned
    ObjectArray *objects = malloc(sizeof(ObjectArray));
    objects->size = 0;
    objects->objects = malloc(sizeof(Object) * objects->size);

    // while loop that continues unitll it reaches the end of the json objects 
    while(parser->token != '}'){

        // the switch statement switches the state its in
        switch (parser->token){
            case '{':
                state = OBJMODE;
            break;
            case ',':
                state = OBJMODE;
            break;
            case '}':
                state = BREAK;
            break;
            default:
                state = SEARCH;
            break;
        }

        // this goes into each individual state function
        switch (state){
            // search state gets a character from the lexer
            case SEARCH:
                parser->token = lexer(&parser->file, &parser->cursor);
            break;
            // objmode state then goes into starting to create a object
            // objmode function also makes the subobject and also will continue to call lexer to get more tokens
            // and also returns a object
            case OBJMODE:
                objects->size += 1;
                objects->objects = realloc(objects->objects, sizeof(Object) * objects->size);
                objects->objects[objects->size - 1] = objMode(parser);
            break;
            default:
            break;    
        }

        if(state == BREAK){
            break;
        }
    }
    return objects;
}
Object *objMode(Parser *parser){
    parser->token = lexer(&parser->file, &parser->cursor);

    // we initialize the object were going to create
    Object *currObj = createObj();
    Node *head;

    // we will then go even deeper and get the object name and other subobjs
    // We'll continue to interate through the json file until we reach a quotation marks 
    // for this level if we run into a '"' that means we have a string and 
    while(parser->token != '}'){
        switch (parser->token) {
            // we'll get that full string and put it as the obj name
            case '"':
                currObj->objName = parseString(parser);
            break;
            // Then we'll go another level deeper and start getting the subobjs that will make our nodes to then attach to to the obj
            case '{':
                // we'll go one more so the subobjmode doesnt see the '{' token and confuse it with its job
                // parser->cursor += 1;
                head = subObjMode(parser);
                currObj->subObjs = head;
            break;
            // if we run into ':' or just whitespace just continue untill we get a token that is meaningful
            default:
                parser->token = lexer(&parser->file, &parser->cursor);
            break;
        }
    }
    // incremeant by one so its either either a comma or blank space
    parser->token = lexer(&parser->file, &parser->cursor);
    return currObj;
}

Node *subObjMode(Parser *parser){
    Node *newNode;
    Node *next = NULL;
    char *key;
    JsonValue value;

    parser->token = lexer(&parser->file, &parser->cursor);

    // i want to first get the key and then get the value of the node
    // value will continue running until it reaches a comma or }
    // if the token is a comma we know we have another subobj to connect the node
    // once we reach the comma we call subobj again create another node and return it so then  
    // i want to then create the node using the key and value 
    if(parser->token == '}'){
        return NULL;
    }

    while(parser->token != '}'){
        switch (parser->token){
            case '"':
                key = parseString(parser);
            break;
            case ':':
                value = parseValue(parser);
            break;
            case ',':
                next = subObjMode(parser);
            break;
            default:
                parser->token = lexer(&parser->file, &parser->cursor);
            break;
        }
    }
    newNode = createNode(key, value, next);
    return newNode;
}

char *parseString(Parser *parser){
    parser->token = lexer(&parser->file, &parser->cursor);
    
    int length = 0;
    int curPtr = parser->cursor;
    char token;

    while((token = parser->file[curPtr]) != '"'){
        length++;
        curPtr++;
    }

    char *string = malloc(length + 1);
    memcpy(string, &parser->file[parser->cursor], length);
    string[length] = '\0';

    parser->cursor = curPtr + 1;
    parser->token = parser->file[parser->cursor];
    return string;
}

double parseNumber(Parser *parser, int *placeMent){
    char *end;

    int length = 0;
    int curPtr = parser->cursor;
    char token;

    while((token = parser->file[curPtr]) == '.' || (token >= '0' && token <= '9')){
        length++;
        curPtr++;
    }

    char *strNum = malloc(length + 1);
    memcpy(strNum, &parser->file[parser->cursor], length);
    strNum[length] = '\0';

    parser->cursor = curPtr;
    parser->token = token;

    double value = strtod(strNum, &end);

    char *placePtr = strchr(strNum, '.');
    *placeMent = placePtr != NULL ? (int)(end - placePtr - 1) : 0;
    
    return value;
}

JsonValue parseValue(Parser *parser){
    parser->token = lexer(&parser->file, &parser->cursor);

    JsonValue value = {0};

    switch(parser->token){
        case '"':
            value.type = STRING;
            value.data.string = parseString(parser);
        break;
        case 'f':
            value.type = BOOL;
            value.data.boolean = false;
        break;
        case 't':
            value.type = BOOL;
            value.data.boolean = true;
        break;
        default:
            value.type = NUMBER;
            value.data.number = parseNumber(parser, &value.placeMent);
        break;
    }

    return value;
}