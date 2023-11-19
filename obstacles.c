#include "obstacles.h"
#include "game.h"
#include "utils.h"
#include "display.h"

void init_obstacles(OBSTACLE obstacles[NUM_OBSTACLES], SPRITES *sprites)
{
    int pos_y = TOTAL_HEIGHT - 3 * MARGIN;
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

void draw_obstacles(OBSTACLE obstacles[NUM_OBSTACLES], SPRITES *sprites)
{
    for (int i = 0; i < NUM_OBSTACLES; i++)
    {
        scale_image(sprites->obstacles[0], obstacles[i].x, obstacles[i].y, 2);
    }
}