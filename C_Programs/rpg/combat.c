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
    // Declare a can run bool for whenever the player tries to run it checks if they can
    bool canRun = true;

    // Wants you reach a certine point of attempts it make can run false
    int runAttempts = 0;

    while(true){
        clearScreen();
        char userInput[3];
    
        // Start to create the display for what the player sees
        // refer to combatDisplay.c for all the combat prints
        combatHeaderDisplay();
        playerDisplay((*player), &(*DB)->itemDB);
        enemyDisplay(enemies);
    
        // We create strOption and actionOption exactly the same so when the player choose one option from strOptions
        // It matches the coorosponding one in actionOptions
        char *strOptions[] = {"Attack", "Inventory", "Attempt to Run"};
        ACTIONS actionOptions[] = {ATTACK, USEITEM, RUNATT};
    
        actionsDisplay(strOptions ,canRun);
    
        fgets(userInput, sizeof(userInput), stdin);
        if(!clearBuffer((int)sizeof(userInput) ,userInput)){
            continue;
        }

        // Turn the userinput into and actual integer so we can match it the the actionOptions Array
        int userInt = *userInput - '0';

        // input check to see if its in range of the options
        if(userInt > 3 || userInt < 1){
            validOption();
            enterContinue();
            getchar();
            continue;
        }

        // assign the the player action
        ACTIONS playerAction = actionOptions[userInt - 1];

        // declare nect and based on next we decide weather to continue or return to dungeon.c entrance function
        DungeonReturns next;
        switch(playerAction){
            case ATTACK:
                next = selectTarget(player, enemies, DB);
            break;
            case USEITEM:
                displayInventoryItems((*player), (*DB)->itemDB);
                next = FIGHT;
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
    // Put into a while true so if the player type something in wrong we can loop back and they can try again
    while(true){
        char userInput[3];

        // Refer to combatDisplay for all prints and displays
        selTargetDisplay((*enemies));
    
        fgets(userInput, sizeof(userInput), stdin);
        if(!clearBuffer((int)sizeof(userInput) ,userInput)){
            continue;
        }

        // Put userinput into a integer format and we can get what enemy the player chose
        int userInt = *userInput - '0';
        if(userInt < 0 || userInt > (*enemies)->enemiesCount){
            validOption();
            enterContinue();
            getchar();
            continue;
        }

        // we put the enemey the player chose into a variable for ease of acces
        Enemy *targetEnemy = (*enemies)->enemies[userInt - 1]; 

        // The send through attack target and attack target changes the player health and does the calculations for damage
        // The returns and Enemy type which is the enemies health
        targetEnemy = attackTarget(player, targetEnemy, (*DB)->itemDB);

        // We then check if either the player or the enemy died
        WHO whosDead = checkDead(player, &targetEnemy);

        // if player died we return DIED and it goes all the way back to dungeon.c entrance
        if(whosDead == PLAYER){
            return DIED;

        // if enemy died we check if all the enemies are ded if so return enemydeafeated
        }else if(whosDead == ENEMEY){
            if(enemiesStatus((*enemies)) == ENEMEYDEFEATED){
                return ENEMEYDEFEATED;
            }
        }

        // Then set the actual enemy to the enemy variable we edited
        (*enemies)->enemies[userInt - 1] = targetEnemy;
        return FIGHT;
    }


}

Enemy *attackTarget(Player **player, Enemy *enemy, ItemDatabase *itemDB){
    //Entually add beingable to see a text of your attack
    // Also being able to chhose a specific attack

    // First we see who gets the initiative with a roll refer to rollInitiative
    WHO initRoll = rollInitiative((*player), enemy);

    // We then roll to see if they can hit eachother
    double playertoHitRoll = toHitRoll(D20, 0, 1);
    double enemytoHitRoll = toHitRoll(D20, 0, 1);

    // We then get theyre weapons and armor to then calculate how much dmg they do to eachother
    Item *playerWeapon = getItemById(itemDB, (*player)->weapon);
    Item *playerArmor = getItemById(itemDB, (*player)->armorSet);

    Item *enemyWeapon = getItemById(itemDB, enemy->weapon);
    Item *enemyArmor = getItemById(itemDB, enemy->armor);

    // Refer to getDamageRoll, but it takes the weapon roll, dmgreduction from the armor, and pentration from the weapon
    double playerDamage = getDamageRoll(playerWeapon->rollData.roll, (*player)->strength, enemyArmor->effectData.dmgReduction, playerWeapon->effectData.penetration);
    double enemyDamage = getDamageRoll(enemyWeapon->rollData.roll, enemy->strength, playerArmor->effectData.dmgReduction, enemyWeapon->effectData.penetration);

    // So we then go into the forloop so that both of them csn get a turn to attack
    for(int i = 0; i < 2; i++){
        switch(initRoll){
            case PLAYER:
                // We first check if the player missed by comparing acs and tohitroll for player if both of them
                // are lower then the player missed
                if((*player)->AC < enemy->AC && playertoHitRoll < enemy->AC){
                    printf("Player Missed");
                }
                // This just checks if the enemy is still alive if he is he can do damage if not print enemy died
                else if((*player)->health > 0){
                    // If either the ac is higher or tohit is higher the player does dammage
                    enemy->health -= playerDamage;

                    // Eventually we'll add a little scene to imagine the fight
                    printf(" PLayer did %.2lf damage", playerDamage);
                }else{
                    printf(" Player Died");
                }
            break;
            case ENEMEY:
                // same thing with player if enemy has lower ac and tohitroll is lower then player ac
                // enemy misses
                if( enemy->AC < (*player)->AC && enemytoHitRoll < (*player)->AC){
                    printf("Enemy Missed");
                }
                // This just checks if the enemy is still alive if he is he can do damage if not print enemy died
                else if(enemy->health > 0){
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

        // After one round we can change who attacks net=xt
        initRoll = initRoll == PLAYER ? ENEMEY : PLAYER;
    }
    getchar();
    return enemy;
}

WHO rollInitiative(Player *player, Enemy *enemy){
    // We create dice for player and enemy becuase eventually some thing may attribute to initiative
    Roll playerInit = {D20, 1};
    Roll enemyInit = {D20, 1};

    // compares the two rolls who ever rolls higher is returned
    if(rollDice(playerInit) > rollDice(enemyInit)){
        return PLAYER;
    }
    return ENEMEY;
}

double toHitRoll(DICETYPE type, double attModifier, int rolls){
    // literally just created roll struct and then roll the dice and add the modifier
    Roll roll = {type,rolls};
    return rollDice(roll) + attModifier;
}

double getDamageRoll(Roll roll, double statModifier, double armorDmgReduct, double weaponPen){
    double dmgPercentage = 0.60;

    // we multiply statmodifier and dmgPercentage so the its not so high
    double baseDmg = statModifier *dmgPercentage;
    // We then roll the weapon dice
    double damage = rollDice(roll) + baseDmg;

    // Next we're going to see if the armor can reduce the damage while also seeing if
    // the weapons pentration is great enough to ignore the armor
    double penAndArmorDmg = max(0, armorDmgReduct - weaponPen);
    double armorEffect = penAndArmorDmg / (penAndArmorDmg + 20);

    // then we add it to the damage
    damage *= (1 - armorEffect);

    return damage;
}

WHO checkDead(Player **player, Enemy **enemy){
    // check the both enemy and player health to see if theyre at 0 and if it is returns the one who is
    // if neither then returns noone
    if((*player)->health <= 0){
        return PLAYER;
    }else if((*enemy)->health <= 0){
        (*enemy)->isDead = true;
        return ENEMEY;
    }
    return NOONE;
}

DungeonReturns enemiesStatus(EnemyDataBase *enemies){
    // goes through all eneimies in dungeon node and checks to see if theyre dead
    // if all of them are dead return enemydeafeted other wise fight to contniue
    for(int i = 0; i < enemies->enemiesCount; i++){
        if(enemies->enemies[i]->isDead == false){
            return FIGHT;
        }
    }
    return ENEMEYDEFEATED;
}



