#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "stdbool.h"

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    int max = 4;
    int row = 0;
    int col = 0;

    char map[10][10];

    for(int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            map[i][j] = '.';
        }
    }

    int path = 65;

    // go either right left up or down based on 0 - 3
    // if the array where we're going already has a letter A - Z then do it again 3 times then terminate
    
    while(path <= 90)
    {
        int move = rand() % 4;
    
        if(map[row + 1][col] != '.' && map[row -1][col] != '.' && map[row][col -1] != '.' && map[row][col +1] != '.')
        {
            break;
        }   
        
        switch (move)
        {
        case 0:
            // go left
            if(row -1 < 0 || map[row -1][col] != '.') continue;
            else if(map[row -1][col] == '.'){
                map[row--][col] = path;
                path++;
            }
        break;
        case 1:
            // go right
            if((row +1) > 10 || map[row + 1][col] != '.') continue; 
            if(map[row +1][col] == '.'){
                map[row++][col] = path;
                path++;
            }
        break;
        case 2:
            // go up
            if((col -1) < 0 || map[row][col -1] != '.') continue; 
            if(map[row][col -1] == '.'){
                map[row][col--] = path;
                path++;
            }
        break;
        case 3:
            // go down
            if((col +1) > 10 || map[row][col +1] != '.')continue; 
            if(map[row][col +1] == '.'){
                map[row][col++] = path;
                path++;
            }
        break;
        
        default:
            printf("something is wrong");
        break;
        }
    }

    for(int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            printf("  %c", map[i][j]);
        }
        printf("\n");
    }



    // if 0 or 1 we go left or right in the row by 1
    // if 2 or 3 we go up or down in the cols by 1
    getchar();




    return 0;
}
