#ifndef COMBAT
#define COMBAT

#include "dungeonMenus.h"
#include "dungeons.h"
#include "entityStructs.h"
#include "fileHandle.h"

typedef enum{
    PLAYER,
    ENEMEY,
    NOONE
}WHO;

DungeonReturns fightMenu(Player **player, EnemeyDataBase **enemies, Database **DB);
DungeonReturns selectTarget(Player **player, EnemeyDataBase **enemies, Database **DB);
Enemey *attackTarget(Player **player, Enemey *enemey, ItemDatabase *itemDB);

WHO checkDead(Player **player, Enemey **enemey);
DungeonReturns enemiesStatus(EnemeyDataBase *enemies);
WHO rollInitiative(Player *player, Enemey *enemey);
double damageRoll(DiceType type, double multiplier, int rolls);

#endif