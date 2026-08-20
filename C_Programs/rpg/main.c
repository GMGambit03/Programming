#include "Headers/gameLoop.h"
// Entity Structs are included from gameLoop
int main(){

    int loadSave = startMenu();

    if(loadSave == 1){
        GameState *gameState = newGameIntro();
    }

    mainLoop(gameState);

    return 0;
}