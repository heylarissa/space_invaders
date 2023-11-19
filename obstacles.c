#include "obstacles.h"
#include "game.h"

void init_obstacles(OBSTACLE obstacles[NUM_OBSTACLES], SPRITES *sprites)
{
    int pos_y = 200;
    int pos_x = 50;
    for (int i = 0; i < NUM_OBSTACLES; i++)
    {
        obstacles[i].y = pos_y;
        obstacles[i].x = pos_x;
        obstacles[i].life = OBSTACLE_LIFE;
        obstacles[i].w = al_get_bitmap_width(sprites->obstacles[0]);
        obstacles[i].h = al_get_bitmap_height(sprites->obstacles[0]);
    }
}