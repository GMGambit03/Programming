#include "Headers/dungeonGeneration.h"
#include "Headers/entityStructs.h"
#include "Headers/fileHandle.h"

void enqueue(Queue *queue, DungeonNode *room, Direction parent){
    // We first make space for the struct itself
    QueueEntry *newEntry = malloc(sizeof(QueueEntry));

    // Then we start giving the newEntry values that we passed in
    newEntry->room = room;
    newEntry->parent = parent;
    newEntry->next = NULL;

    // Then we check if we already have an entry in queue 
    // if we dont then we set the our new entry to the front and rear of the queue
    if(queue->rear == NULL){
        queue->front = newEntry;
        queue->rear = newEntry;
    }
    // if we do then we set the rear next to our newentry 
    // and make the newEntry our rear
    else{
        queue->rear->next = newEntry;
        queue->rear = newEntry;
    }
}

QueueEntry *dequeue(Queue *queue){
    // we first see if we have anything to begin with
    if(queue->front == NULL){
        return NULL;
    }

    // Then we first want to grab hold of the front
    QueueEntry *entry = queue->front;
    // Then we set the new front to be the old fronts next
    queue->front = queue->front->next;

    // Then we check to see if the new front is NULL
    // if so we just make rear NULL
    if(queue->front == NULL){
        queue->rear = NULL;
    }

    // then we return what we got
    return entry;
}

Dungeon *createDungeon(Object *dungeonData){
    Dungeon *dungeonStruct = malloc(sizeof(Dungeon));

    dungeonStruct->dungeonId = getMember(dungeonData, "iD")->value.data.number;
    dungeonStruct->dungeonName = getMember(dungeonData, "Name")->value.data.string;
    dungeonStruct->description = getMember(dungeonData, "Description")->value.data.string;

    // Getting array for possibleEnemies
    JsonArray *dungeonEnemiesArr = getMember(dungeonData, "PossibleEnemies")->value.data.array;
    dungeonEnemiesArr->count--;
    dungeonStruct->possibleEnemies = getIntArr(dungeonEnemiesArr, &dungeonStruct->possEnemyCount); 

    dungeonStruct->minEnemyCnt = getMember(dungeonData, "MinEnemyCount")->value.data.number;
    dungeonStruct->maxEnemyCnt = getMember(dungeonData, "MaxEnemyCount")->value.data.number;

    dungeonStruct->minRooms = getMember(dungeonData, "MinRooms")->value.data.number;
    dungeonStruct->maxRooms = getMember(dungeonData, "MaxRooms")->value.data.number;

    dungeonStruct->dungeonBossId = getMember(dungeonData, "BossId")->value.data.number;
    return dungeonStruct;

}

DungeonNode *createDungeonNode(int roomCount, Dungeon **dungeon, EnemyDataBase **enemyDatabase){

    int count = 0;
    Queue queue = {NULL, NULL};

    //We'll first create our entrance
    DungeonNode *entrance = createRoom(dungeon, enemyDatabase);
    entrance->isEntrance = true;
    (*dungeon)->entrance = entrance;

    count++;

    //We'll then add our entrance to the queue
    enqueue(&queue, entrance, NONE);

    // Now we'll go into a loop of createing each dungeon individually 
    // and adding its children to a queue and basiclly go through that queue 
    // and repeat
    while(count < roomCount && queue.front != NULL){
        // We'll get the room thats in the front and make its children
        QueueEntry *current = dequeue(&queue);

        // make the room we're going to put into the dungeon
        DungeonNode *room = current->room;
        Direction parent = current->parent;

        free(current);

        // makeing an array of the different directions we can have
        Direction direction[4] = {NORTH, EAST, SOUTH, WEST};
        int dirSize = sizeof(direction)/sizeof(*direction);
    
        // we first check if this is child of another room if so we create space for one less direction array
        Direction *direct;
        if(parent != NONE){
            direct = malloc(sizeof(Direction) * 3);
        }else{
            direct = malloc(sizeof(Direction) * 4);
        }
        // we then fill up the new direction array with all the valid directions
        int y = 0;
        int newDirSize = 0;
        for(int i = 0; i < dirSize; i++){
            if(parent != direction[i]){
                direct[y] = direction[i];
                newDirSize++;
                y++;
            }
        }
    
         int dirCnt = 0;
         // The formula is (rand() % (max - min + 1)) + min
        // we then use rand to get rand number of different rooms you can go inside of the actual room
        // If we have 2 or less rooms those rooms will have 2 options the plater can choose from
        if(count <= 2){
            dirCnt = 2;
        }else{
            // if we have moree then its between 0 and 2
            int min = 1;
            dirCnt = newDirSize == dirSize ? (rand() % (dirSize - min + 1)) + min : (rand() % (newDirSize - min + 1)) + min;
        }
    
        // Shuffle the directions so we can just go in a for loop and get the hoever many we randomed for
        for(int i = newDirSize - 1; i > 0; i--){
            int ranNum = rand() % (i + 1);
    
            Direction curr = direct[i];
            Direction swap = direct[ranNum];
    
            direct[i] = swap;
            direct[ranNum] = curr;
        }
    
        for(int i = 0; i < dirCnt && count < roomCount; i++){
            // we create next room equal to our shuffled array starting at 0 and going until it maxes out
            Direction nxtRoom = direct[i];
            Direction childParent;

            // We first initialize the dungeonNode so based one weather we're at the end of the dungeon
            // we can descide on weather its a boss dungeon or not
            DungeonNode *child;
            if(roomCount - 1 == count){
                child = createBossRoom(dungeon, enemyDatabase);
                (*dungeon)->bossRoom = child;
            }else{
                child = createRoom(dungeon, enemyDatabase);
            }

            count++;

            // based on nxtRoom which is the direction we then set the parent for the next room so it knows where this room is
            // if the parent room is just the opistite direction of nxtRoom
            // Then we'll also add the new room to the queue
            switch (nxtRoom) {
                case NORTH:
                    childParent = SOUTH;

                    room->north = child;
                    child->south = room;

                    enqueue(&queue, child, childParent);
                    
                break;
                case WEST:
                    childParent = EAST;
                    
                    room->west = child;
                    child->east = room;

                    enqueue(&queue, child, childParent);

                break;
                case SOUTH:
                    childParent = NORTH;
                    
                    room->south = child;
                    child->north = room;

                    enqueue(&queue, child, childParent);

                break;
                case EAST:
                    childParent = WEST;
                    
                    room->east = child;
                    child->west = room;

                    enqueue(&queue, child, childParent);

                break;
                default:
                break;
            }
        }
        free(direct);
    }
    return entrance;

}

void getDungeonNodes(Dungeon **dungeon, EnemyDataBase **enemyDatabase){
    // this function we just get the max room count and set the dungeon entrance
    // And we declare the count here because in get nodes each child can change the value and it wouldnt be random
    int roomCount = (rand() % ((*dungeon)->maxRooms - (*dungeon)->minRooms + 1)) + (*dungeon)->minRooms;
    (*dungeon)->entrance = createDungeonNode(roomCount, dungeon, enemyDatabase);

    int count = 0;
    int depth = 0;

    printf("%d", roomCount);
    test((*dungeon)->entrance, &count, &depth, "Entrance");
    getchar();
}

DungeonNode *createRoom(Dungeon **dungeon, EnemyDataBase **enemyDatabase){

    // we create a tmp pointer so its easier to type everything
    Dungeon *tmp = (*dungeon);

    // ccreate space for everything we're going to add to the room
    DungeonNode *room = malloc(sizeof(DungeonNode));

    // initially set all the directions to null because not every room will have all the directions
    room->north = NULL;
    room->east = NULL;
    room->west = NULL;
    room->south = NULL;

    // initialize the isEntrance and isBossRoom false so C doesnt give it a random value
    room->isBossRoom = false;
    room->isEntrance = false;

    // we get a random enemy count between the specifc dungeons min and max enemies
    room->enemiesCount = rand() % (tmp->maxEnemyCnt - tmp->minEnemyCnt + 1) + tmp->minEnemyCnt;

    // Just to make it easier for other funtions we check if theyre any enimies even in the dungeon
    if(room->enemiesCount == 0){
        room->enemiesDead = true;
    }else{
        room->enemiesDead = false;
    }

    // we then based on the different enimies the dungeon can have we randomly add them to the room
    room->enemies = getRanEnemies(tmp->possibleEnemies, tmp->possEnemyCount, room->enemiesCount, enemyDatabase);

    // eventually we'll have different descriptions for each room
    room->description = "We dont got anything";

    return room;
}

DungeonNode  *createBossRoom(Dungeon **dungeon, EnemyDataBase **enemyDatabase){
    //This where we explicitly create the bossroom

    // we create a tmp pointer so its easier to type everything
    Dungeon *tmp = (*dungeon);

    // ccreate space for everything we're going to add to the room
    DungeonNode *bossRoom = malloc(sizeof(DungeonNode));

    // initially set all the directions to null because not every room will have all the directions
    bossRoom->north = NULL;
    bossRoom->east = NULL;
    bossRoom->west = NULL;
    bossRoom->south = NULL;

    // initialize the isEntrance to false and the bossRoom to true
    bossRoom->isBossRoom = true;
    bossRoom->isEntrance = false;

    // for right now we're going to make the enemy count just 1 which is going to be the boss itself
    bossRoom->enemiesCount = 1;

    // Just to make it easier for other funtions we check if theyre any enimies even in the dungeon
    if(bossRoom->enemiesCount == 0){
        bossRoom->enemiesDead = true;
    }else{
        bossRoom->enemiesDead = false;
    }

    // we then based on the different enimies the dungeon can have we randomly add them to the room
    bossRoom->enemies = getEnemyById((*dungeon)->dungeonBossId, enemyDatabase);
    bossRoom->enemies->enemiesCount = bossRoom->enemiesCount;

    // eventually we'll have different descriptions for each room
    bossRoom->description = "BossRoom";

    return bossRoom;
}


void test(DungeonNode *root, int *count, int *depth, char* direction){
    if(root == NULL || root->visited){
        return;
    }
    root->visited = true;
    if(root->isBossRoom){
        direction = "BossRoom";
    }

    *count += 1;
    
    for(int i = 0; i < *depth; i++) {
        printf("  │ ");
    }

    printf("└─── [%s] ||| Room #%d\n", direction, *count);

    test(root->north, count, depth + 1, "North");
    test(root->east,  count, depth + 1, "East");
    test(root->south, count, depth + 1, "South");
    test(root->west,  count, depth + 1, "West");
}
