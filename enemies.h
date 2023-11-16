#ifndef __ENEMIES__
#define __ENEMIES__
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include "game.h"
#include "player.h"
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

void init_enemies(ENEMY *enemy);
void init_spaceship(ENEMY *spaceship, SPRITES *sprites);
void init_game(PLAYER *player, ENEMY *enemies, ENEMY *spaceship, SPRITES *sprites);
void update_enemies(ENEMY *enemies, ENEMY *spaceship);
#endif