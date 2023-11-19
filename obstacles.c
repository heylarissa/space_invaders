#include "obstacles.h"
#include "game.h"
#include "utils.h"
#include "display.h"

/* Inicializa obstáculos */
void init_obstacles(OBSTACLE obstacles[NUM_OBSTACLES], SPRITES *sprites)
{
    int pos_y = TOTAL_HEIGHT - 3 * MARGIN;

    for (int i = 0; i < NUM_OBSTACLES; i++)
    {
        if (i == 0)
            obstacles[i].x = MARGIN;
        else
            obstacles[i].x = obstacles[i - 1].x + obstacles[i - 1].w + OBSTACLE_SPACING;
        obstacles[i].y = pos_y;
        obstacles[i].life = OBSTACLE_LIFE;
        obstacles[i].w = al_get_bitmap_width(sprites->obstacles[0]);
        obstacles[i].h = al_get_bitmap_height(sprites->obstacles[0]);
    }
}

/* Desenha obstáculos */
void draw_obstacles(OBSTACLE obstacles[NUM_OBSTACLES], SPRITES *sprites)
{
    for (int i = 0; i < NUM_OBSTACLES; i++)
    {
        scale_image(sprites->obstacles[0], obstacles[i].x, obstacles[i].y, 3);
    }
}