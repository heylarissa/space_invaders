#ifndef __OBSTACLES__
#define __OBSTACLES__

#define NUM_OBSTACLES 5
#define OBSTACLE_LIFE 10

#include "game.h"

typedef struct obstacle
{
    float x, y; // posição
    int w, h;   // tamanho;
    int life;   // vidas
} OBSTACLE;

void init_obstacles(OBSTACLE obstacles[NUM_OBSTACLES], SPRITES *sprites);
void draw_obstacles(OBSTACLE obstacles[NUM_OBSTACLES], SPRITES *sprites);
#endif