#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#include "display.h"
#include "player.h"
#include "enemies.h"
#include "utils.h"
#include "obstacles.h"

void must_init(bool test, const char *description)
{
    if (test)
        return;

    printf("Couldn't initialize %s\n", description);
    exit(1);
}

void init_sprites(SPRITES *sprites)
{
    sprites->_sheet = al_load_bitmap("./assets/sprites.png");
    must_init(sprites->_sheet, "sprites");

    sprites->spaceinvaderslogo = select_sprite(sprites->_sheet, 160, 0, 250, 170);
    sprites->spaceship = select_sprite(sprites->_sheet, 365, 770, 220, 100);
    sprites->player = select_sprite(sprites->_sheet, 350, 1160, 110, 68);

    sprites->explosion_player = select_sprite(sprites->_sheet, 364, 275, (400 - 364), (290 - 275));
    sprites->explosion_enemy = select_sprite(sprites->_sheet, 436, 275, (464 - 436), (290 - 292));

    sprites->shot_intermed = select_sprite(sprites->_sheet, 410, 276, (420 - 410), (289 - 276));
    sprites->shot_strong = select_sprite(sprites->_sheet, 379, 1903, (394 - 379), (1928 - 1903));

    sprites->aliens_t1[0] = select_sprite(sprites->_sheet, 146, 225, 25, 17); // v1
    sprites->aliens_t1[1] = select_sprite(sprites->_sheet, 180, 225, 25, 17); // v2

    sprites->aliens_t2[0] = select_sprite(sprites->_sheet, 73, 225, 25, 17);  // v1
    sprites->aliens_t2[1] = select_sprite(sprites->_sheet, 106, 225, 25, 17); // v2

    sprites->aliens_t3[0] = select_sprite(sprites->_sheet, 35, 225, 25, 17); // v3
    sprites->aliens_t3[1] = select_sprite(sprites->_sheet, 6, 225, 25, 17);  // v3

    sprites->obstacles[0] = select_sprite(sprites->_sheet, 315, 210, 45, 35); // sem dano
    sprites->obstacles[1] = select_sprite(sprites->_sheet, 479, 210, 45, 35); // dano 2
    sprites->obstacles[2] = select_sprite(sprites->_sheet, 479, 263, 45, 35); // dano 4
    sprites->obstacles[3] = select_sprite(sprites->_sheet, 426, 210, 45, 35); // dano 6
    sprites->obstacles[4] = select_sprite(sprites->_sheet, 372, 210, 45, 35); // dano 8
}

void destroy_sprites(SPRITES *sprites)
{
    al_destroy_bitmap(sprites->_sheet);
    al_destroy_bitmap(sprites->spaceinvaderslogo);
    al_destroy_bitmap(sprites->spaceship);

    al_destroy_bitmap(sprites->aliens_t1[0]);
    al_destroy_bitmap(sprites->aliens_t2[0]);
    al_destroy_bitmap(sprites->aliens_t3[0]);

    al_destroy_bitmap(sprites->aliens_t1[1]);
    al_destroy_bitmap(sprites->aliens_t2[1]);
    al_destroy_bitmap(sprites->aliens_t3[1]);

    al_destroy_bitmap(sprites->obstacles[0]);
    al_destroy_bitmap(sprites->obstacles[1]);
    al_destroy_bitmap(sprites->obstacles[2]);
    al_destroy_bitmap(sprites->obstacles[3]);
    al_destroy_bitmap(sprites->obstacles[4]);

    free(sprites);
}

// Seleciona a parte da imagem a ser cortada
ALLEGRO_BITMAP *select_sprite(ALLEGRO_BITMAP *img, int x, int y, int w, int h)
{
    ALLEGRO_BITMAP *sprite = al_create_sub_bitmap(img, x, y, w, h);
    must_init(sprite, "select sprite");
    return sprite;
}

void draw_lives(int lives, ALLEGRO_BITMAP *live, ALLEGRO_FONT *font)
{
    int pos_x = TOTAL_WIDTH - 350;
    int pos_y = 5;
    al_draw_text(font, WHITE, TOTAL_WIDTH - 400, 0, 0, "LIVES ");
    for (int i = 0; i < lives; i++)
    {
        pos_x = pos_x + al_get_bitmap_width(live) * 0.5;
        scale_image(live, pos_x, pos_y, 0.5);
    }
}
