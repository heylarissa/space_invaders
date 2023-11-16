#ifndef __PLAYER__
#define __PLAYER__

#include "game.h"
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

typedef struct player
{
    float x, y;
    int score;
    int lives;
    int w, h;
    float speed;
    SHOT *shots; // lista de tiros ativos

} PLAYER;

#define SIZE_PLAYER 50

void init_player(PLAYER *player, SPRITES *sprites);
void update_player_shots(PLAYER *p);
void create_player_shot(PLAYER *p);

#endif