#include "Headers/parser.h"

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
    // We're going to create linked list for essential the keys and values
    Node *newNode;
    Node *next = NULL;
    char *key;
    JsonValue value;

    // Get rid of all empty space and non important data
    parser->token = lexer(&parser->file, &parser->cursor);

    // i want to first get the key and then get the value of the node
    // value will continue running until it reaches a comma or }
    // if the token is a comma we know we have another subobj to connect the node
    // once we reach the comma we call subobj again create another node and return it so then  
    // i want to then create the node using the key and value 

    // This is a recursive function in a sense in order to link the keys and values to eachother 
    // Whenever we encounter a closing bracket we know we reached the end and assign the next value to the last Node created
    if(parser->token == '}'){
        return NULL;
    }

    while(parser->token != '}'){
        switch (parser->token){
            // we first encounter the quotations and return everything inside the quotes and end on the semicolon
            case '"':
                key = parseString(parser);
            break;
            // When we encounter a colon we can start getting the value
            case ':':
                value = parseValue(parser);
            break;
            // This is the recursive part we call subobjmode again and return the node it creates
            case ',':
                next = subObjMode(parser);
            break;
            // Get rid of empty space or non important characters
            default:
                parser->token = lexer(&parser->file, &parser->cursor);
            break;
        }
    }
    // using the previous created nodes and theyre returns we can create a new node with the next node being the different keys
    newNode = createNode(key, value, next);
    // return the new node and repeat
    return newNode;
}

char *parseString(Parser *parser){
    // When we encounter a string set prev to the start of the quotes just in case we need to go back
    parser->prev = parser->cursor;
    // Get rid of empty space and non important charcters
    parser->token = lexer(&parser->file, &parser->cursor);
    
    // in this little while loop we're basically going count the amount of characters that is in between the two quotes
    int length = 0;
    int curPtr = parser->cursor;
    char token;

    while((token = parser->file[curPtr]) != '"'){
        length++;
        curPtr++;
    }

    // We then use the length we got from the while loop to create space for the new string
    // Then we memcpy using the *string as the destination, the starter pointer at the first quotation marks and the length of characters
    char *string = malloc(length + 1);
    memcpy(string, &parser->file[parser->cursor], length);
    string[length] = '\0';

    // Then we set the parser point cursor +1 of where the while ptrcursor was so we step off of the quotations and not go back in parsestring
    parser->cursor = curPtr + 1;
    // do the same for the token so we dont think we're still on the quotations token
    parser->token = parser->file[parser->cursor];
    return string;
}

double parseNumber(Parser *parser, int *placeMent){
    // We're going to be using strtod so we have to define a end
    // What strtod does is basically just start at the beginning of the string pointer you give it
    // and keep going until it finds the beginning of a number character and then continues untill it finds the end of a number
    char *end;

    // We're first going to go a head a parse the number and put it into a string so its easier for strtod to get the numbers
    // and not get something it doesnt need
    // refer to parsestring for what going on
    int length = 0;
    int curPtr = parser->cursor;
    char token;

    // Only difference is we keep going until token is not a number or a decimal point
    while((token = parser->file[curPtr]) == '.' || (token >= '0' && token <= '9')){
        length++;
        curPtr++;
    }

    // same thing as parsestring except we're not going up by one we're just setting it equal because there no indicator after a number
    char *strNum = malloc(length + 1);
    memcpy(strNum, &parser->file[parser->cursor], length);
    strNum[length] = '\0';

    parser->cursor = curPtr;
    parser->token = token;

    // use strtod on the parsed numstring and turn it into a double to use 
    double value = strtod(strNum, &end);

    // This first finds if there was a decmial in the strNum
    // strchr on success of finding the given char or string it returns a pointer to the start of where it found the match
    // so example "34.56" useing strchr with '.' itll return a *char at '.' and if you print it. it'll print ".56"  
    char *placePtr = strchr(strNum, '.');
    // So we use strchr to get where the '.' is in our number 
    // When we use strtod end points to one more of where the last number was
    // so we subtract the memaddr of end and placePtr and - 1 to account for ends one more and we get the postion of the '.' to use for the display
    *placeMent = placePtr != NULL ? (int)(end - placePtr - 1) : 0;

    free(strNum);
    
    return value;
}

JsonValue parseValue(Parser *parser){
    // bypass spaces and non inportant chars
    parser->token = lexer(&parser->file, &parser->cursor);

    // We ste this to zero because of the placement type for numbers
    // if its a string it wont ever not be zer0
    JsonValue value = {0};

    // using Jsonvalue enum to give the type a readable value
    switch(parser->token){
        case '"':
            value.type = STRING;
            value.data.string = parseString(parser);
        break;
        case 'f':
            // This is temporary asoon as you feel like please replce this with a better validation/cursor increase
            //Asssonsnso as s sposssibleelel change
            // This sucks but im lazy
            parser->cursor += 4;
            value.type = BOOL;
            value.data.boolean = false;
        break;
        case 't':
            // This is temporary asoon as you feel like please replce this with a better validation/cursor increase
            // Change thissssisissisi
            parser->cursor += 3;
            value.type = BOOL;
            value.data.boolean = true;
        break;
        // This is one of the main reasons for prev
        // Now if we run into a object within another object we want to go back to the first quotations 
        // we can then give the new basically subobject a name and go through the entire process
        // We do minus one because at the beginning of objmode it increases the cursor so we want to make sure 
        // We stay on quotations when we enter objmode
        case '{':
            parser->cursor = parser->prev - 1;
            value.type = OBJECT;
            value.data.obj = objMode(parser);
        break;
        default:
            value.type = NUMBER;
            value.data.number = parseNumber(parser, &value.placeMent);
        break;
    }

    return value;
}