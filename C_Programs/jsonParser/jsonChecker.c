#include "Headers/jsonChecker.h"

bool checkFile(char *fileName){
    char *target = ".json";
    int fileSizeName = strlen(fileName);

    int ptr = 0;
    int state = NONCOMP;

    for(int i = 0; i < fileSizeName; i++){
        char curr = fileName[i];

        if(curr == '.'){
            state = COMP;
        }
        if (state == COMP) {
            if(curr == target[ptr]){
                ptr++;
            }else{
                return false;
            }
            }
            if(ptr - 1 == (int)strlen(target) - 1){
                return true;
            }
    }
    return false;
}