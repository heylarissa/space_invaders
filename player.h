#ifndef __PLAYER__
#define __PLAYER__

#include "display.h"

#include "enemies.h"
#include "obstacles.h"

#define PLAYER_SHOT_SPEED 10
#define PLAYER_SPEED 15

enum PLAYER_STATE {
    alive,
    explode
};

typedef struct player
{
    float x, y;
    int score;
    int lives;
    int state;
    int w, h;
    float speed;
    SHOT *shots; // lista de tiros ativos

} PLAYER;

#define SIZE_PLAYER 50

void init_player(PLAYER *player, SPRITES *sprites);
void draw_player(SPRITES *sprites, PLAYER player);
void destroy_player(PLAYER *player);
void move_player(unsigned char key[], PLAYER *player);
void create_player_shot(PLAYER *p);
#endif