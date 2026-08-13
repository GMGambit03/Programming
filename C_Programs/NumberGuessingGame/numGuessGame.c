#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void gameLoop(int difficulty){

    int maxTries = 0;
    int tries = 0;
    int guess;
    int numToGuess = (rand() % 101);
    bool didWin = false;

    switch (difficulty)
    {
    case 1:
        maxTries = 10;
        break;
    
    case 2:
        maxTries = 5;
        break;

    case 3:
        maxTries = 3;
        break;
    
    default:
        printf("Something is wrong");
        exit(1);
        break;
    }

    while(didWin == false)
    {

        printf("Guess a number between 1 and 100 you have %d ", (maxTries - tries));

        switch (maxTries - tries)
        {
        case 1:
            printf("try left: ");
            break;
        
        default:
            printf("tries left: ");
            break;
        }

        scanf("%d", &guess);

        if(guess > numToGuess){
            printf("%d", guess);
            printf(" is to large try a smaller number\n");
            tries++;
        }
        else if (guess < numToGuess) {
            printf("%d", guess);
            printf(" is too small, try a bigger number\n");
            tries++;
        }
        else if(guess == numToGuess){
            printf("Thats insane you were able to guess the number in %d", tries);
            printf(" tries\n");
            didWin = true;
        }
        
        if((tries + 1) > maxTries){
            printf("Your absolute bunzz, maybe try winning in another universe\n");
            break;
        }
    }

}

int main(int argc, char const *argv[])
{
    firstStart: 
    ;

    bool didWin = false;
    bool played = false;

    srand(time(NULL));

    int difficulty = 0;

    if(played){
        didWin = false;
        printf("Please choose difficulty:\n Easy(1), Hard(2), Impossible(3)");
        scanf("%d", &difficulty);
    }
    else{
        printf("Please choose difficulty:\n Easy(1), Hard(2), Impossible(3)");
        scanf("%d", &difficulty);        
    }

    if(difficulty < 0 || difficulty > 3 ){
        goto firstStart;
    }
    else{
        gameLoop(difficulty);
    }

    played = true;
    goto firstStart;
}


