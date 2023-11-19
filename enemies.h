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

#define ENEMY_SPACING 50
#define NUM_ENEMIES_LINES 5
#define ENEMIES_PER_LINE 11
#define ENEMY_SPEED 30

#define SIZE_ENEMY 25
#define ENEMY_STATE_ONE 0
#define ENEMY_STATE_TWO 1
#define DEAD_ENEMY (-1)
#define IGNORE_ENEMY (-2)

#define ENEMY_SHOOTING_LIMIT 2

enum ENEMY_TYPE
{
    weak = 1,
    intermed = 2,
    strong = 3
};

typedef struct enemy // apenas 2 inimigos podem atirar
{
    float x, y;
    int width, height; // tamanho da imagem
    int type;          // existem 3 tipos de inimigos + spaceship - define qual sprite será exibida
    SHOT *shots;       // tiro do inimigo - um por vez
    int direction;     // direita / esquerda
    int state;         // vivo img 1, vivo img 2 e quando morre.
} ENEMY;

void init_enemies(SPRITES *sprites, ENEMY (*enemies)[ENEMIES_PER_LINE]);
void init_spaceship(ENEMY *spaceship, SPRITES *sprites);
void update_enemies(ENEMY (*enemies)[ENEMIES_PER_LINE], ENEMY *spaceship);
void draw_enemies(ENEMY enemies[NUM_ENEMIES_LINES][ENEMIES_PER_LINE], SPRITES *sprites);
int get_enemy_type(int line);
void move_enemies(ENEMY (*enemies)[ENEMIES_PER_LINE]);
void move_red_spaceship(ENEMY *spaceship);
bool checkAllEnemiesDefeated(ENEMY (*enemies)[ENEMIES_PER_LINE]);
#endif