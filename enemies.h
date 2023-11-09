#ifndef __ENEMIES__
#define __ENEMIES__
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include "game.h"
typedef struct enemy // apenas 2 inimigos podem atirar
{
    float x, y;
    int size;
    int r, g, b; // cor do inimigo
    int type;    // existem 3 tipos de inimigos + spaceship
    int alive;   // vivo?
    SHOT shot;   // tiro do inimigo - um por vez
    int direction;
    struct enemy *next;
} ENEMY;


#endif