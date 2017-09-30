#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dun_utils.h"
#include "priority_queue.h"

void createMonsters(monster_t *arr, int size);

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
    * End of handling user inputs and arguments
    * Start of generating monsters with characteristics
    */

    
    srand(time(NULL));

    monster_t monsters[num_monsters];
    createMonsters(monsters, num_monsters);
    printf("The PC will move on turn %d\n", event_constant/10);

    /**
     * End of monster generation
     * Start of character movement
     */
     
    return 0;
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