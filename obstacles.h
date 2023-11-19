#ifndef __OBSTACLES__
#define __OBSTACLES__

#define NUM_OBSTACLES 5
#define OBSTACLE_LIFE 10

#include "game.h"
#include "display.h"
#include "enemies.h"

#define OBSTACLE_SPACING 290

typedef struct obstacle
{
    float x, y; // posição
    int w, h;   // tamanho;
    int life;   // vidas
} OBSTACLE;

void init_obstacles(OBSTACLE obstacles[NUM_OBSTACLES], SPRITES *sprites);
void draw_obstacles(OBSTACLE obstacles[NUM_OBSTACLES], SPRITES *sprites);
bool obstacle_collision(OBSTACLE obstacles[NUM_OBSTACLES], SHOT shot, int enemy_type);

#endif