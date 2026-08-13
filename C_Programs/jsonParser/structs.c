#include "Headers/structs.h"

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