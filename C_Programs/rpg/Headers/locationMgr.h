#ifndef LOCATIONMGR
#define LOCATIONMGR

typedef struct{
    int iD;
    char *name;

    int nextLocation;

    int shops;
    int dungeons;

    int dungeonCompletions;
    int questCompleted;
    int requiredItem;
}Location;

typedef struct{
    Location **location;
    int size;
}LocationDatabase;

#endif