#ifndef STRUCTS
#define STRUCTS

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct JsonValue JsonValue;
typedef struct Node Node;
typedef struct Object Object;
typedef struct JsonArray JsonArray;

typedef enum {
    BOOL,
    NUMBER,
    STRING,
    OBJECT,
    ARRAY
}JsonType;

typedef struct JsonValue{
    JsonType type;
    int placeMent;

    union{
        bool boolean;
        double number;
        char *string;
        Object *obj;
        JsonArray *array;
    }data;
}JsonValue;

typedef struct JsonArray{
    JsonValue *values;
    int count;
    int capacity;
}JsonArray;

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

typedef struct{
    char *key;
    JsonValue value;
}Member;

Object *createObj();
Node *createNode(char *key, JsonValue value, Node *next);
Object *getObject(ObjectArray *objArray, char *objName);
Member *getObjArrayMember(ObjectArray *objArray, char *objName, char *key);
Member *getMember(Object *object, char *key);
int *getIntArr(JsonArray *jsonArray, int *count);
void freeObj(Object *object);

void printObj(Object *object);
void printValue(JsonValue value);

#endif