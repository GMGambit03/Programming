#include "Headers/structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Object *createObj(){
    Object *object = malloc(sizeof(Node));
    object->objName = NULL;
    object->subObjs = NULL;
    return object;
}

Node *createNode(char *key, JsonValue value, Node *next){
    Node *node = malloc(sizeof(Node));
    node->key = strdup(key);
    node->value = value;
    node->next = next;

    return node;
}

Member *getObjArrayMember(ObjectArray *objArray, char *objName, char *key){
    Member *member = malloc(sizeof(Member));

    Object *object = getObject(objArray, objName);
    if(object == NULL){
        return NULL;
    }

    Node *tmpNode = object->subObjs;
    while(tmpNode != NULL){
        if(strcmp(tmpNode->key, key) == 0){
            member->key = tmpNode->key;
            member->value = tmpNode->value;
            return member;
        }
        else{
            tmpNode = tmpNode->next;
        }
    }
    if(tmpNode == NULL){
        free(member);
        return NULL;
    }
    return member;
}

Member *getMember(Object *object, char *key){
    Member *member = malloc(sizeof(Member));

    Node *tmpNode = object->subObjs;
    while(tmpNode != NULL){
        if(strcmp(tmpNode->key, key) == 0){
            member->key = tmpNode->key;
            member->value = tmpNode->value;
            return member;
        }
        else{
            tmpNode = tmpNode->next;
        }
    }
    if(tmpNode == NULL){
        free(member);
        return NULL;
    }
    return member;
}

Object *getObject(ObjectArray *objArray, char *objName){
    int objLength = objArray->size;

    for(int i = 0; i < objLength; i++){
        Object *currObj = objArray->objects[i];
        char *currObjName = currObj->objName;
        int compare = strcmp(currObjName, objName);

        if(compare == 0){
            return currObj;
        }
    }
    return NULL;
}

int *getIntArr(JsonArray *jsonArray, int *count){
    int *array = malloc(sizeof(int) * jsonArray->count);

    for(int i = 0; i < jsonArray->count; i++){
        if(jsonArray->values[i].type != NUMBER){
            continue;
        }
        int currInt = jsonArray->values[i].data.number;
        array[i] = currInt;
        *count += 1;
    }

    return array;
}

void freeObj(Object *object){

    while(object->subObjs != NULL){
        Node *nxtNode = object->subObjs->next;
        free(object->subObjs);
        object->subObjs = nxtNode;
        nxtNode = nxtNode->next;
    }
    free(object);
}

void printValue(JsonValue value){
    switch (value.type){
        case STRING:
            printf("%s", value.data.string);
        break;
        case BOOL:
            if(value.data.boolean == 0){
                printf("False");
            }else{
                printf("True");
            }
        break;
        case NUMBER:
            printf("%.*lf", value.placeMent, value.data.number);
        break;
        default:
        break;
    }
    printf("\n");
}

void printObj(Object *object){
    Object *tmpObj = object;
    Node *tmpNode = tmpObj->subObjs;

    printf("%s\n", tmpObj->objName);

    while(tmpNode != NULL){
        printf("    %s: ", tmpNode->key);

        printValue(tmpNode->value);

        tmpNode = tmpNode->next;
    }
}