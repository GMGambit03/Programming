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

DungeonReturns fightMenu(Player **player, EnemyDataBase **enemies, Database **DB){
    bool canRun = true;
    int runAttempts = 0;

    while(true){
        clearScreen();
        char userInput[3];
    
        combatHeaderDisplay();
        playerDisplay((*player), &(*DB)->itemDB);
        enemyDisplay(enemies);
    
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

DungeonReturns selectTarget(Player **player, EnemyDataBase **enemies, Database **DB){
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

        Enemy *targetEnemy = (*enemies)->enemies[userInt - 1]; 

        targetEnemy = attackTarget(player, targetEnemy, (*DB)->itemDB);

        WHO whosDead = checkDead(player, &targetEnemy);

        if(whosDead == PLAYER){
            return DIED;
        }else if(whosDead == ENEMEY){
            if(enemiesStatus((*enemies)) == ENEMEYDEFEATED){
                return ENEMEYDEFEATED;
            }
        }

        (*enemies)->enemies[userInt - 1] = targetEnemy;
        getchar();
        return FIGHT;
    }


}

Enemy *attackTarget(Player **player, Enemy *enemy, ItemDatabase *itemDB){
    int baseDef = 8;
    //Entually add beingable to see a text of your attack
    // Also being able to chhose a specific attack
    WHO initRoll = rollInitiative((*player), enemy);
    double playerDef = (*player)->speed + baseDef;
    double eneDef = enemy->speed + baseDef;

    double playertoHitRoll = damageRoll(D20, 0, 1);
    double enemytoHitRoll = damageRoll(D20, 0, 1);

    double playerDamage = (*player)->strength;
    double enemyDamage = enemy->strength;

    for(int i = 0; i < 2; i++){
        switch(initRoll){
            case PLAYER:
                if(playerDef < eneDef && playertoHitRoll < eneDef){
                    printf("Player Missed");
                }else{
                    playerDamage = applyArmor(playerDamage, enemy->armor, itemDB);
                    enemy->health -= playerDamage;
                    printf(" PLayer did %.2lf damage", playerDamage);
                }
            break;
            case ENEMEY:
                if( eneDef < playerDef && enemytoHitRoll < eneDef){
                    printf("Enemy Missed");
                }else if(enemy->health > 0){
                    enemyDamage = applyArmor(enemyDamage, (*player)->armorSet, itemDB);
                    (*player)->health -= enemyDamage;
                    printf(" Enemy did %.2lf damage", enemyDamage);
                }else{
                    printf(" Enemy Died");
                }
            break;
            default:
                printf("Nothing Happen");
            break;
        }

        initRoll = initRoll == PLAYER ? ENEMEY : PLAYER;
    }
    getchar();
    return enemy;
}

WHO rollInitiative(Player *player, Enemy *enemy){
    Roll playerInit = {D20, player->speed, 1};
    Roll enemyInit = {D20, enemy->speed, 1};

    if(rollDice(playerInit) > rollDice(enemyInit)){
        return PLAYER;
    }
    return ENEMEY;
}

double damageRoll(DiceType type, double dmgReduction, int rolls){
    Roll roll = {type, dmgReduction, rolls};
    return rollDice(roll);
}

WHO checkDead(Player **player, Enemy **enemy){
    if((*player)->health <= 0){
        return PLAYER;
    }else if((*enemy)->health <= 0){
        (*enemy)->isDead = true;
        return ENEMEY;
    }
    return NOONE;
}

DungeonReturns enemiesStatus(EnemyDataBase *enemies){
    for(int i = 0; i < enemies->enemiesCount; i++){
        if(enemies->enemies[i]->isDead == false){
            return FIGHT;
        }
    }
    return ENEMEYDEFEATED;
}



