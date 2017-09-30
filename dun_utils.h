#ifndef DUN_UTILS_H
#define DUN_UTILS_H

#define dungeon_rows 21
#define dungeon_columns 80
#define num_rooms 6

typedef struct vertex
{
    int distance;
    int x_position;
    int y_position;

}vertex_t;

typedef struct sptSet
{
    int size;
    vertex_t *vertex;
} sptSet_t;



char distances_non_tunnel[dungeon_rows][dungeon_columns];
char distances_tunnel[dungeon_rows][dungeon_columns];
char dungeon[dungeon_rows][dungeon_columns];
int rooms[num_rooms][4];
int hardness[dungeon_rows][dungeon_columns];
int pc_x_position;
int pc_y_position;

void print_dungeon(void);
int gen_dun(void);
void place_PC(void);

#endif