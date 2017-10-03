#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dun_utils.h"
#include "priority_queue.h"

void createMonsters(monster_t *arr, int size);
void placeMonsters(monster_t *arr, int size);

int main(int argc, char* argv[])
{
    int num_monsters = 0;
    //int turn = 0;

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

            printf("Setting dungeon up for %d monsters\n", num_monsters);
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

     monster_t firstToMove;
     queue_peek(q,&firstToMove);
     printf("The first monster to move is %x, at %d,%d\n", firstToMove.characteristics, firstToMove.x_pos, firstToMove.y_pos);
     
     queue_delete(q);
     free(q);

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
        printf("Characteristics for monster %d is %x and speed is %d and is moving in turn %d\n", index, arr[index].characteristics, arr[index].speed, arr[index].move);
    }
}