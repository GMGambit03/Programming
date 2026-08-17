#include "Headers/combat.h"
#include "Headers/dialogue.h"
#include "Headers/dice.h"
#include "Headers/dungeonMenus.h"
#include "Headers/dungeons.h"
#include "Headers/entityStructs.h"
#include "Headers/combatDisplay.h"
#include "Headers/itemHelper.h"
#include "Headers/stringHelpers.h"
#include <stdbool.h>
#include <stdio.h>

DungeonReturns fightMenu(Player **player, EnemeyDataBase **enemies, Database **DB){
    bool canRun = true;
    int runAttempts = 0;

    while(true){
        clearScreen();
        char userInput[3];
    
        combatHeaderDisplay();
        playerDisplay((*player), &(*DB)->itemDB);
        enemeyDisplay(enemies);
    
        char *strOptions[] = {"Attack", "Use Item", "Attempt to Run"};
        ACTIONS actionOptions[] = {ATTACK, USEITEM, RUNATT};
    
        actionsDisplay(strOptions ,canRun);
    
        fgets(userInput, sizeof(userInput), stdin);
        if(!clearBuffer((int)sizeof(userInput) ,userInput)){
            continue;
        }

        int userInt = *userInput - '0';
        if(userInt > 3 || userInt < 1){
            validOption();
            enterContinue();
            getchar();
            continue;
        }

        ACTIONS playerAction = actionOptions[userInt - 1];

        DungeonReturns next;
        switch(playerAction){
            case ATTACK:
                next = selectTarget(player, enemies, DB);
            break;
            case USEITEM:
                // next = useItem(player, enemies, (*DB)->itemDB);
            break;
            case RUNATT:
                if(runAttempts == 3){
                    canRun = false;
                }
                // bool runAttempt = runAttempt();
                // runAttempts++;
            break;
        }

        if(next != FIGHT){
            return next;
        }

    }

    return FIGHT;

}

DungeonReturns selectTarget(Player **player, EnemeyDataBase **enemies, Database **DB){
    while(true){
        char userInput[3];

        selTargetDisplay((*enemies));
    
        fgets(userInput, sizeof(userInput), stdin);
        if(!clearBuffer((int)sizeof(userInput) ,userInput)){
            continue;
        }

        int userInt = *userInput - '0';
        if(userInt < 0 || userInt > (*enemies)->enemiesCount){
            validOption();
            enterContinue();
            getchar();
            continue;
        }

        Enemey *targetEnemey = (*enemies)->enemies[userInt - 1]; 

        targetEnemey = attackTarget(player, targetEnemey, (*DB)->itemDB);

        WHO whosDead = checkDead(player, &targetEnemey);

        if(whosDead == PLAYER){
            return DIED;
        }else if(whosDead == ENEMEY){
            if(enemiesStatus((*enemies)) == ENEMEYDEFEATED){
                return ENEMEYDEFEATED;
            }
        }

        (*enemies)->enemies[userInt - 1] = targetEnemey;
        getchar();
        return FIGHT;
    }


}

Enemey *attackTarget(Player **player, Enemey *enemey, ItemDatabase *itemDB){
    //Entually add beingable to see a text of your attack
    // Also being able to chhose a specific attack
    WHO initRoll = rollInitiative((*player), enemey);
    double playerDef = (*player)->speed + 8;
    double eneDef = enemey->speed + 8;

    double playerDamage = damageRoll(D6, (*player)->strength, 2);

    double enemeyDamage = damageRoll(D6, enemey->strength, 2);

    for(int i = 0; i < 2; i++){
        switch(initRoll){
            case PLAYER:
                if(playerDef < eneDef && playerDamage < eneDef){
                    printf("Player Missed");
                }else{
                    playerDamage = applyArmor(playerDamage, enemey->armor, itemDB);
                    enemey->health -= playerDamage;
                    printf(" PLayer did %.2lf damage", playerDamage);
                }
            break;
            case ENEMEY:
                if( eneDef < playerDef && eneDef < playerDamage){
                    printf("Enemey Missed");
                }else if(enemey->health > 0){
                    enemeyDamage = applyArmor(enemeyDamage, (*player)->armorSet, itemDB);
                    (*player)->health -= enemeyDamage;
                    printf(" Enemey did %.2lf damage", enemeyDamage);
                }else{
                    printf(" Enemey Died");
                }
            break;
            default:
                printf("Nothing Happen");
            break;
        }

        initRoll = initRoll == PLAYER ? ENEMEY : PLAYER;
    }
    getchar();
    return enemey;
}

WHO rollInitiative(Player *player, Enemey *enemey){
    Roll playerInit = {D20, player->speed, 1};
    Roll enemeyInit = {D20, enemey->speed, 1};

    if(rollDice(playerInit) > rollDice(enemeyInit)){
        return PLAYER;
    }
    return ENEMEY;
}

double damageRoll(DiceType type, double multiplier, int rolls){
    Roll roll = {type, multiplier, rolls};
    return rollDice(roll);
}

WHO checkDead(Player **player, Enemey **enemey){
    if((*player)->health <= 0){
        return PLAYER;
    }else if((*enemey)->health <= 0){
        (*enemey)->isDead = true;
        return ENEMEY;
    }
    return NOONE;
}

DungeonReturns enemiesStatus(EnemeyDataBase *enemies){
    for(int i = 0; i < enemies->enemiesCount; i++){
        if(enemies->enemies[i]->isDead == false){
            return FIGHT;
        }
    }
    return ENEMEYDEFEATED;
}



