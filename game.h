#ifndef __GAME__
#define __GAME__
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#define TRUE 1
#define FALSE 0

#define LEFT 0
#define RIGHT 1

#define UP 1
#define DOWN (-1)
// player sprite will require two costumes, a regular one and a dead one
// a sprite for the player, aliens, spaceship and bullets
typedef struct SPRITES_T
{
    ALLEGRO_BITMAP *_sheet;

    ALLEGRO_BITMAP *spaceship;

    ALLEGRO_BITMAP *aliens_t1[2]; // Fracos, não atiram caso exista uma entidade à sua frente ou se já existir um projétil na coluna, causam um (1) de dano em obstáculos;
    ALLEGRO_BITMAP *aliens_t2[2]; // Intermediários, não atiram caso exista um projétil na coluna, causam dois (2) de dano em obstáculos;
    ALLEGRO_BITMAP *aliens_t3[2]; // Fortes, podem atirar mesmo se existir até um projétil na coluna, causam dois (2) de dano em obstáculos.

    ALLEGRO_BITMAP *player;
    ALLEGRO_BITMAP *shield[5];
    ALLEGRO_BITMAP *spaceinvaderslogo;
    ALLEGRO_BITMAP *explosion;
    ALLEGRO_BITMAP *shot;

} SPRITES;

typedef struct shot
{
    int direction;
    float x, y;
    struct shot *next;
} SHOT;


void init_sprites(SPRITES *sprites);
ALLEGRO_BITMAP *select_sprite(ALLEGRO_BITMAP *img, int x, int y, int w, int h);
void draw_lives(int lives, ALLEGRO_BITMAP *live, ALLEGRO_FONT *font);
void delete_shot(int position, SHOT **head);

#endif