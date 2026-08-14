#ifndef JSONPARSER
#define JSONPARSER

#include <stdbool.h>
#include <stddef.h>

// ======== jsonChecker ========
bool checkFile(const char *fileName); 

// ======== GetFile ========
char *getJsonFile(const char *fileName);

// ======== Json Structs ========
typedef enum {
    JSON_BOOL,
    JSON_NUMBER,
    JSON_STRING,
    JSON_ARRAY
}JsonType;

typedef struct JsonValue JsonValue;
typedef struct Member Member;

// ======== Object Structs =======
typedef struct Node Node;
typedef struct Object Object;
typedef struct ObjectArray ObjectArray;

// ======== Parser Structs =======

typedef struct Parser Parser;

// Object Functions
Object *getObject(ObjectArray *objArray, const char *objName);
Member *getMember(ObjectArray *objArray, const char *objcName, const char *key);

void printObj(Object *object);
void printValue(JsonValue value);
void freeObj(Object *object);

// ======== Parser Functions ========
ObjectArray *searchMode(Parser *parser);

#endif