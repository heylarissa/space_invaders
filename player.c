#include "display.h"
#include "player.h"
#include "shots.h"
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include "utils.h"

void init_player(PLAYER *player, SPRITES *sprites)
{
    player->x = WIDTH_DISPLAY / 2;
    player->y = HEIGHT_DISPLAY - SIZE_PLAYER;
    player->score = 0;
    player->lives = 3;
    player->shots = NULL;
    player->state = alive;
    player->w = al_get_bitmap_width(sprites->player);
    player->h = al_get_bitmap_height(sprites->player);
}

void destroy_player(PLAYER *player)
{
    SHOT *aux;
    aux = player->shots;
    player->shots = NULL;
    free(aux);
}

void draw_player(SPRITES *sprites, PLAYER player)
{

    if (player.state == explode)
    {
        scale_image(sprites->explosion_player, player.x + 5, player.y + player.h / 2, 2);
        al_flip_display();
        sleep(1);
        al_draw_scaled_bitmap(sprites->explosion_player, 0, 0,
                              al_get_bitmap_width(sprites->explosion_player),
                              al_get_bitmap_height(sprites->explosion_player),
                              player.x + player.w / 2 + 5, player.y + player.h / 2,
                              -al_get_bitmap_width(sprites->explosion_player) * 2,
                              al_get_bitmap_height(sprites->explosion_player) * 2, 0);
        al_flip_display();
        sleep(1);
        scale_image(sprites->explosion_player, player.x + 5, player.y + player.h / 2, 2);
        al_flip_display();
        sleep(1);
    }
    else
        al_draw_bitmap(sprites->player, player.x, player.y, 0);
    draw_player_shots(player.shots);
}
