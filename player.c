#include "display.h"
#include "player.h"
#include "shots.h"
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

void init_player(PLAYER *player, SPRITES *sprites)
{
    player->x = WIDTH_DISPLAY / 2;
    player->y = HEIGHT_DISPLAY - SIZE_PLAYER;
    player->score = 0;
    player->lives = 3;
    player->shots = NULL;
    player->w = al_get_bitmap_width(sprites->player);
    player->h = al_get_bitmap_height(sprites->player);
}

void draw_player(SPRITES *sprites, PLAYER player)
{
    al_draw_bitmap(sprites->player, player.x, player.y, 0);
    draw_player_shots(player.shots);
}
