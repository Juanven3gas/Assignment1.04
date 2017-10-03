#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include "dun_utils.h"
#include "priority_queue.h"

void createMonsters(monster_t *arr, int size);
void placeMonsters(monster_t *arr, int size);
int moveMonster(monster_t m);
int checkForPC(monster_t m);
int charToInt(char c);
char intToChar(int i);

int game_won = 0;

int main(int argc, char* argv[])
{
    int num_monsters = 0;
    int turn = 0;

    //Check the argumens
    //and handle user inputs
    if(argc < 3)
    {
        printf("Insufficient arguements\n");
        return 1;
    }

    int arg_count = 1;
    while(arg_count < argc)
    {
        if(strcmp(argv[arg_count],  "--nummon") == 0)
        {
            arg_count++;
            num_monsters = atoi(argv[arg_count]);
            if(num_monsters <= 0)
            {
                printf("Incorrect argument passed\n");
                return 1;
            }

            //printf("Setting dungeon up for %d monsters\n", num_monsters);
            arg_count++;
        }
        else 
        {
            printf("incorrect argument detected: %s\n", argv[arg_count]);
            return 1;
        }
    }

    /**
    *End of handling user inputs and arguments
    *Start of setting up the dungeon and the distances array
    */

    calc_distances();

    /**
    * End setting up dungeon
    * Start of generating monsters with characteristics and place them in a random place in the dungeon
    */
    srand(time(NULL));

    monster_t monsters[num_monsters];
    createMonsters(monsters, num_monsters);
    placeMonsters(monsters, num_monsters);
    print_dungeon();
    
    /**
     * End of monster generation
     * Start of character movement
     */
    
     queue_t *q = (queue_t *) malloc(sizeof(queue_t));
     queue_init(q);
     int index;
     for(index = 0; index < num_monsters; index++)
     {
         int priority = event_constant / monsters[index].speed;
         queue_add(q,monsters[index], priority);
     }

     int game_finished = 0;
     
     while(!game_finished)
     {
         //Grab the first monster to move
         monster_t toMove;
         queue_remove(q, &toMove);

         if(toMove.alive)
         {
            printf("Monster %x at %d,%d will move\n", toMove.characteristics, toMove.x_pos, toMove.y_pos);
            game_finished = moveMonster(toMove);
            queue_add(q, toMove, (event_constant/toMove.speed) + turn++);
            print_dungeon();
         }
     }
     
     if(!game_won)
     {
         printf("GAME OVER PLAYER WAS EATEN BY MONSTER!!\n");
     }
     else
     {
         printf("GAME WON ALL MONSTER DESTROYED!!\n");
     }
     print_dungeon();
     //monster_t firstToMove;
     //queue_peek(q,&firstToMove);
     //printf("The first monster to move is %x, at %d,%d\n", firstToMove.characteristics, firstToMove.x_pos, firstToMove.y_pos);
     

     queue_delete(q);
     free(q);

    return 0;
}

int moveMonster(monster_t m)
{
    
    int pcFound = checkForPC(m);

    if(pcFound)
    {
        return 1;
    }

    if(m.characteristics == 0x0)
    {
        return 0;
    }
    else if (m.characteristics == 0x1)
    {
        return 0;   
    }
    else if(m.characteristics == 0x2)
    {
        return 0;
    }
    else if(m.characteristics == 0x3)
    {
        //printf("Monster has a 0x3 charicteristic\n");
        int minX = 0;
        int minY = 0;
        int min = INT_MAX;
        //Get all 8 positions and see what is available
        if(distances_non_tunnel[m.x_pos+1][m.y_pos] != ' ')
        {
            if(distances_non_tunnel[m.x_pos+1][m.y_pos] == '@')
            {
                //move the monster over and win the game
                dungeon[m.x_pos+1][m.y_pos] = '3';
                return 1;
            }
            int dis = distances_non_tunn[m.x_pos+1][m.y_pos];
            if(dis < min)
            {
                min = dis;
                minX = m.x_pos+1;
                minY = m.y_pos;
            }
            
        }
        if(distances_non_tunnel[m.x_pos-1][m.y_pos] != ' ')
        {
            if(distances_non_tunnel[m.x_pos-1][m.y_pos] == '@')
            {
                dungeon[m.x_pos-1][m.y_pos] = '3';
                return 1;
            }
            int dis = distances_non_tunn[m.x_pos-1][m.y_pos];
            if(dis < min)
            {
                min = dis;
                minX = m.x_pos-1;
                minY = m.y_pos;
            }
            
        }
        if(distances_non_tunnel[m.x_pos][m.y_pos+1] != ' ')
        {
            if(distances_non_tunnel[m.x_pos][m.y_pos+1] == '@')
            {
                dungeon[m.x_pos][m.y_pos+1] = '3';
                return 1;
            }
            
            int dis = distances_non_tunn[m.x_pos][m.y_pos+1];
            if(dis < min)
            {
                min = dis;
                minX = m.x_pos;
                minY = m.y_pos+1;
            }
        }
        if(distances_non_tunnel[m.x_pos][m.y_pos-1] != ' ')
        {
            if(distances_non_tunnel[m.x_pos][m.y_pos-1] == '@')
            {
                dungeon[m.x_pos][m.y_pos-1] = '3';
                return 1;
            }
            int dis = distances_non_tunn[m.x_pos][m.y_pos-1];
            if(dis < min)
            {
                min = dis;
                minX = m.x_pos;
                minY = m.y_pos-1;
            }
        }
        if(distances_non_tunnel[m.x_pos+1][m.y_pos-1] != ' ')
        {
            if(distances_non_tunnel[m.x_pos+1][m.y_pos-1] == '@')
            {
                dungeon[m.x_pos+1][m.y_pos-1] = '3';
                return 1;
            }
            int dis = distances_non_tunn[m.x_pos+1][m.y_pos-1];
            if(dis < min)
            {
                min = dis;
                minX = m.x_pos+1;
                minY = m.y_pos-1;
            }
        }
        if(distances_non_tunnel[m.x_pos+1][m.y_pos+1] != ' ')
        {
            if(distances_non_tunnel[m.x_pos+1][m.y_pos+1] == '@')
            {
                dungeon[m.x_pos+1][m.y_pos+1] = '3';
                return 1;
            }
            int dis = distances_non_tunn[m.x_pos+1][m.y_pos+1];
            if(dis < min)
            {
                min = dis;
                minX = m.x_pos+1;
                minY = m.y_pos+1;
            }
        }
        if(distances_non_tunnel[m.x_pos-1][m.y_pos+1] != ' ')
        {
            if(distances_non_tunnel[m.x_pos-1][m.y_pos+1] == '@')
            {
                dungeon[m.x_pos-1][m.y_pos+1] = '3';
                return 1;
            }
            int dis = distances_non_tunn[m.x_pos-1][m.y_pos+1];
            if(dis < min)
            {
                min = dis;
                minX = m.x_pos-1;
                minY = m.y_pos+1;
            }
        }
        if(distances_non_tunnel[m.x_pos-1][m.y_pos-1] != ' ')
        {
            if(distances_non_tunnel[m.x_pos-1][m.y_pos-1] == '@')
            {
                dungeon[m.x_pos-1][m.y_pos-1] = '3';
                return 1;
            }
            int dis = distances_non_tunn[m.x_pos-1][m.y_pos-1];
            if(dis < min)
            {
                min = dis;
                minX = m.x_pos-1;
                minY = m.y_pos-1;
            }
            
        }

        dungeon[minX][minY] = '3';
        dungeon[m.x_pos][m.y_pos] = '.';
        m.x_pos = minX;
        m.y_pos = minY;
        return 0;
    }
    else if(m.characteristics == 0x4)
    {
        return 0;
    }
    else if(m.characteristics == 0x5)
    {
        return 0;
    }
    else if(m.characteristics == 0x6)
    {
        return 0;
    }
    else if(m.characteristics == 0x7)
    {
        return 0;
    }
    else if(m.characteristics == 0x8)
    {
        return 0;
    }
    else if(m.characteristics == 0x9)
    {
        return 0;
    }
    else if (m.characteristics == 0xa)
    {
        return 0;
    }
    else if (m.characteristics == 0xb)
    {
        return 0;   
    }
    else if (m.characteristics == 0xc)
    {
        return 0;
    }
    else if (m.characteristics == 0xd)
    {
        return 0;
    }
    else if (m.characteristics == 0xe)
    {
        return 0;
    }
    else if (m.characteristics == 0xf)
    {
        return 0;
    }
    
    return 0;
}

int checkForPC(monster_t m)
{
    if(dungeon[m.x_pos +1][m.y_pos] == '@')
    {
        dungeon[m.x_pos+1][m.y_pos] = intToChar(m.characteristics);
        dungeon[m.x_pos][m.y_pos] = '.';
        return 1;
    }
    else if(dungeon[m.x_pos -1][m.y_pos] == '@')
    {
        dungeon[m.x_pos-1][m.y_pos] = intToChar(m.characteristics);
        dungeon[m.x_pos][m.y_pos] = '.';
        return 1;
    }
    else if(dungeon[m.x_pos][m.y_pos+1] == '@')
    {
        dungeon[m.x_pos][m.y_pos+1] = intToChar(m.characteristics);
        dungeon[m.x_pos][m.y_pos] = '.';
        return 1;
    }
    else if(dungeon[m.x_pos][m.y_pos-1] == '@')
    {
        dungeon[m.x_pos][m.y_pos-1] = intToChar(m.characteristics);
        dungeon[m.x_pos][m.y_pos] = '.';
        return 1;
    }
    else if(dungeon[m.x_pos +1][m.y_pos+1] == '@')
    {
        dungeon[m.x_pos+1][m.y_pos+1] = intToChar(m.characteristics);
        dungeon[m.x_pos][m.y_pos] = '.';
        return 1;
    }
    else if(dungeon[m.x_pos +1][m.y_pos-1] == '@')
    {
        dungeon[m.x_pos+1][m.y_pos-1] = intToChar(m.characteristics);
        dungeon[m.x_pos][m.y_pos] = '.';
        return 1;
    }
    else if(dungeon[m.x_pos -1][m.y_pos+1] == '@')
    {
        dungeon[m.x_pos-1][m.y_pos+1] = intToChar(m.characteristics);
        dungeon[m.x_pos][m.y_pos] = '.';
        return 1;
    }
    else if(dungeon[m.x_pos -1][m.y_pos-1] == '@')
    {
        dungeon[m.x_pos-1][m.y_pos-1] = intToChar(m.characteristics);
        dungeon[m.x_pos][m.y_pos] = '.';
        return 1;
    }

    return 0;
}
void placeMonsters(monster_t *arr, int size)
{
    int index;
    srand(time(NULL));

    for(index = 0; index < size; index++)
    {
        //Pick a random room
        int room = rand() % num_rooms;

        int room_rows = rooms[room][0];
        int room_cols = rooms[room][1];
        int room_start_row = rooms[room][2];
        int room_start_col = rooms[room][3];

        int temp1 = (room_start_row + room_rows) -1;
        int temp2 = (room_start_col + room_cols) -1;
        
        int temp3 = room_start_row - temp1;
        int temp4 = room_start_col - temp2;
    
        //Pick a random position in that room so long as there is nothing there
        int success = 0;
        while(!success)
        {
            int monster_start_row = (rand() % temp3) + room_start_row;
            int monster_start_col = (rand() % temp4) + room_start_col;

            if(dungeon[monster_start_row][monster_start_col] == '.')
            {
                //place the character of the monster
                int characteristics = arr[index].characteristics;
                arr[index].x_pos = monster_start_row;
                arr[index].y_pos = monster_start_col;
                success = 1;

                switch (characteristics)
                {
                    case 0x0 :
                    dungeon[monster_start_row][monster_start_col] = '0';
                    break;
                    case 0x1 :
                    dungeon[monster_start_row][monster_start_col] = '1';
                    break;
                    case 0x2 :
                    dungeon[monster_start_row][monster_start_col] = '2';
                    break;
                    case 0x3 :
                    dungeon[monster_start_row][monster_start_col] = '3';
                    break;
                    case 0x4 :
                    dungeon[monster_start_row][monster_start_col] = '4';
                    break;
                    case 0x5 :
                    dungeon[monster_start_row][monster_start_col] = '5';
                    break;
                    case 0x6 :
                    dungeon[monster_start_row][monster_start_col] = '6';
                    break;
                    case 0x7 :
                    dungeon[monster_start_row][monster_start_col] = '7';
                    break;
                    case 0x8 :
                    dungeon[monster_start_row][monster_start_col] = '8';
                    break;
                    case 0x9 :
                    dungeon[monster_start_row][monster_start_col] = '9';
                    break;
                    case 0xa :
                    dungeon[monster_start_row][monster_start_col] = 'a';
                    break;
                    case 0xb :
                    dungeon[monster_start_row][monster_start_col] = 'b';
                    break;
                    case 0xc :
                    dungeon[monster_start_row][monster_start_col] = 'c';
                    break;
                    case 0xd :
                    dungeon[monster_start_row][monster_start_col] = 'd';
                    break;
                    case 0xe :
                    dungeon[monster_start_row][monster_start_col] = 'e';
                    break;
                    case 0xf :
                    dungeon[monster_start_row][monster_start_col] = 'f';
                    break;
                    default :
                    dungeon[monster_start_row][monster_start_col] = 'g';
                }
            }
        }
    }
}

void createMonsters(monster_t *arr, int size)
{
    int index;
    for(index = 0; index < size; index++)
    {
        int characteristics = rand() & 0xf;
        int speed = (rand() % 15) + 5;
        arr[index].characteristics = characteristics;
        arr[index].speed = speed;
        arr[index].move = event_constant / speed;
        arr[index].alive = 1;
        //printf("Characteristics for monster %d is %x and speed is %d and is moving in turn %d\n", index, arr[index].characteristics, arr[index].speed, arr[index].move);
    }
}

int charToInt(char c)
{
    switch(c)
    {
        case '0':
        return 0;
        case '1':
        return 1;
        case '2':
        return 2;
        case '3':
        return 3;
        case '4':
        return 4;
        case '5':
        return 5;
        case '6':
        return 6;
        case '7':
        return 7;
        case '8':
        return 8;
        case '9':
        return 9;
    }

    return 0;
}

char intToChar(int i)
{
    switch(i)
    {
        case 0:
        return '0';
        case 1:
        return '1';
        case 2:
        return '2';
        case 3:
        return '3';
        case 4:
        return '4';
        case 5:
        return '5';
        case 6:
        return '6';
        case 7:
        return '7';
        case 8:
        return '8';
        case 9:
        return '9';
        case 10:
        return 'a';
        case 11:
        return 'b';
        case 12:
        return 'c';
        case 13:
        return 'd';
        case 14:
        return 'e';
        case 15:
        return 'f';
    }

    return '0';
}