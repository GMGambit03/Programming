#ifndef JSONSTRUCTS
#define JSONSTRUCTS

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
    int placeMent;

    union{
        bool boolean;
        double number;
        char *string;
    }data;
}JsonValue;

typedef struct{
    int size;
    Object **objects;
}ObjectArray;

typedef struct Object{
    int id;
    char *objName;
    Node *subObjs;
}Object;

typedef struct Node{
    char *key;
    JsonValue value;
    struct Node *next;
}Node;

typedef struct{
    char *key;
    JsonValue value;
}Member;

Object *createObj();
Node *createNode(char *key, JsonValue value, Node *next);
Object *getObject(ObjectArray *objArray, char *objName);
Member *getMember(Object *obj, char *key);
void getId(Object **obj);
void freeObj(Object *object);

void printObj(Object *object);
void printValue(JsonValue value);

#endif