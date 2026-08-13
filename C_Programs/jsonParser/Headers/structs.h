#ifndef STRUCTS
#define STRUCTS

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct JsonValue JsonValue;
typedef struct Node Node;
typedef struct Object Object;

typedef enum {
    BOOL,
    NUMBER,
    STRING,
    ARRAY
}JsonType;

typedef struct JsonValue{
    JsonType type;

    union{
        bool boolean;
        int placeMent;
        double number;
        char *string;
    }data;
}JsonValue;

typedef struct{
    int size;
    Object **objects;
}ObjectArray;

typedef struct Object{
    char *objName;
    Node *subObjs;

}Object;

typedef struct Node{
    char *key;
    JsonValue value;
    struct Node *next;
}Node;

Object *createObj();
Node *createNode(char *key, JsonValue value, Node *next);

void printObj(Object *object);
void printValue(JsonValue value);

#endif