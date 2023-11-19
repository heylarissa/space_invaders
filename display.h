#ifndef __DISPLAY__
#define __DISPLAY__

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#define GREEN al_map_rgb(52, 255, 0)
#define WHITE al_map_rgb(255, 255, 255)
#define RED al_map_rgb(255, 0, 0)
#define BLACK al_map_rgb(0, 0, 0)

#define HEIGHT_DISPLAY 800
#define WIDTH_DISPLAY 1600
#define MARGIN 100
#define TOTAL_WIDTH WIDTH_DISPLAY + MARGIN
#define TOTAL_HEIGHT HEIGHT_DISPLAY + MARGIN

#define KEY_SEEN 1
#define KEY_RELEASED 2

typedef struct
{
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_TIMER *timer;
    ALLEGRO_DISPLAY *display;
    ALLEGRO_FONT *font;
} WINDOW;

#define TRUE 1
#define FALSE 0

#define LEFT 0
#define RIGHT 1

#define UP 1
#define DOWN (-1)

typedef struct SPRITES_T
{
    ALLEGRO_BITMAP *_sheet;

    ALLEGRO_BITMAP *spaceship;

    ALLEGRO_BITMAP *aliens_t1[2]; // Fracos, não atiram caso exista uma entidade à sua frente ou se já existir um projétil na coluna, causam um (1) de dano em obstáculos;
    ALLEGRO_BITMAP *aliens_t2[2]; // Intermediários, não atiram caso exista um projétil na coluna, causam dois (2) de dano em obstáculos;
    ALLEGRO_BITMAP *aliens_t3[2]; // Fortes, podem atirar mesmo se existir até um projétil na coluna, causam dois (2) de dano em obstáculos.

    ALLEGRO_BITMAP *player;
    ALLEGRO_BITMAP *spaceinvaderslogo;

    ALLEGRO_BITMAP *explosion_player;
    ALLEGRO_BITMAP *explosion_enemy;

    ALLEGRO_BITMAP *shot_weak;
    ALLEGRO_BITMAP *shot_intermed;
    ALLEGRO_BITMAP *shot_strong;

    ALLEGRO_BITMAP *obstacles[5];

} SPRITES;

typedef struct shot
{
    int direction;
    int state;
    float x, y;
    struct shot *next;
} SHOT;

typedef enum
{
    MENU,
    GAME,
    GAME_OVER,
    PAUSED
} GameState;

void init_sprites(SPRITES *sprites);
ALLEGRO_BITMAP *select_sprite(ALLEGRO_BITMAP *img, int x, int y, int w, int h);
void draw_lives(int lives, ALLEGRO_BITMAP *live, ALLEGRO_FONT *font);
void destroy_sprites(SPRITES *sprites);
void must_init(bool test, const char *description);


#endif