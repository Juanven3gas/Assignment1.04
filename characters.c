#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dun_utils.h"

int main(int argc, char* argv[])
{
    int num_monsters = 0;

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

    /*
    * End of handling user inputs and arguments
    * Start of generating monsters with characteristics
    */

    int index;
    for(index = 0; index < num_monsters; index++)
    {
        
    }

    return 0;
}