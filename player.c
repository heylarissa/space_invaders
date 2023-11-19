#include "display.h"
#include "player.h"
#include "shots.h"
#include "utils.h"

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
void move_player(unsigned char key[], PLAYER *player)
{
    if (key[ALLEGRO_KEY_LEFT] && (player->x >= 0))
        player->x -= PLAYER_SPEED;
    else if (key[ALLEGRO_KEY_RIGHT] && player->x <= (TOTAL_WIDTH - player->w))
        player->x += PLAYER_SPEED;
    else if (key[ALLEGRO_KEY_SPACE])
        create_player_shot(player);
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
