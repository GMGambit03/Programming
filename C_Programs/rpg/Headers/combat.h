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

DungeonReturns fightMenu(Player **player, EnemyDataBase **enemies, Database **DB);
DungeonReturns selectTarget(Player **player, EnemyDataBase **enemies, Database **DB);
Enemy *attackTarget(Player **player, Enemy *enemy, ItemDatabase *itemDB);

WHO checkDead(Player **player, Enemy **enemy);
DungeonReturns enemiesStatus(EnemyDataBase *enemies);
WHO rollInitiative(Player *player, Enemy *enemy);
double toHitRoll(DICETYPE type, double attModifier, int rolls);
double getDamageRoll(Roll roll, double statModifier, double armorDmgReduct, double weaponPen);

#endif