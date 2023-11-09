#ifndef __PLAYER__
#define __PLAYER__

#include "game.h"

typedef struct player
{
    float x, y;
    int score;
    int lives;
    int w, h;
    SHOT *shots; // lista de tiros ativos

} PLAYER;

#define SIZE_PLAYER 50

#endif