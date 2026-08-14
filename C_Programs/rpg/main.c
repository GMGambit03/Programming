#include "Headers/gameLoop.h"
int main(int argc, const char *argv[]){

    int loadSave = startMenu();
    Player *player;

    switch(loadSave){
        case 1:
            player = newGameIntro();
        break;
    }

    return 0;
}