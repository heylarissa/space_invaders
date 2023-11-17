#ifndef __ENEMIES__
#define __ENEMIES__
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "display.h"
#include "game.h"
#include "player.h"
#include "enemies.h"
#include "shots.h"

#define ENEMY_SPACING 70
#define NUM_ENEMIES_LINES 5
#define ENEMIES_PER_LINE 11
#define ENEMY_DESLOC (TOTAL_WIDTH / 4)

#define SIZE_ENEMY 50
#define ENEMY_STATE_ONE 1
#define ENEMY_STATE_TWO 2
#define DEAD_ENEMY 0


typedef struct enemy // apenas 2 inimigos podem atirar
{
    float x, y;
    int size; // tamanho da imagem
    int type;    // existem 3 tipos de inimigos + spaceship - define qual sprite será exibida
    int alive;   // vivo? o espaço deve permanecer, porém o inimigo não é exibido
    SHOT *shots;   // tiro do inimigo - um por vez
    int direction; // direita / esquerda
    int line; // número da linha
    int state; // vivo img 1, vivo img 2 e quando morre.
    struct enemy *next;
} ENEMY;

ENEMY *init_enemies();
void init_spaceship(ENEMY *spaceship, SPRITES *sprites);
void update_enemies(ENEMY *enemies, ENEMY *spaceship);
void draw_enemies(ENEMY *enemies, SPRITES *sprites);

#endif