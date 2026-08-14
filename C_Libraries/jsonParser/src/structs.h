#ifndef STRUCTS
#define STRUCTS

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../include/jsonParser.h"

typedef struct JsonValue JsonValue;
typedef struct Node Node;
typedef struct Object Object;

struct JsonValue{
    JsonType type;
    int placeMent;

    union{
        bool boolean;
        double number;
        char *string;
    }data;
};

struct ObjectArray{
    int size;
    Object **objects;
};

struct Object{
    char *objName;
    Node *subObjs;

};

struct Node{
    char *key;
    JsonValue value;
    struct Node *next;
};

struct Member{
    char *key;
    JsonValue value;
};

Object *createObj();
Node *createNode(const char *key, JsonValue value, Node *next);
Object *getObject(ObjectArray *objArray, const char *objName);
Member *getMember(ObjectArray *objArray, const char *objcName, const char *key);
void freeObj(Object *object);

void printObj(Object *object);
void printValue(JsonValue value);

#endif