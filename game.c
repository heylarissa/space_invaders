#include "game.h"
#include "display.h"
#include "player.h"
#include "enemies.h"

void init_sprites(SPRITES *sprites)
{
    sprites->_sheet = al_load_bitmap("./assets/sprites.png");
    must_init(sprites->_sheet, "sprites");

    sprites->spaceinvaderslogo = select_sprite(sprites->_sheet, 160, 0, (410 - 160), 170);
    sprites->spaceship = select_sprite(sprites->_sheet, 365, 770, (585 - 365), (870 - 770));
    sprites->player = select_sprite(sprites->_sheet, 350, 1160, (460 - 350), (1228 - 1160));

    sprites->aliens_t1[0] = select_sprite(sprites->_sheet, 146, 225, (171 - 146), (242 - 225)); // v1
    sprites->aliens_t1[1] = select_sprite(sprites->_sheet, 180, 225, (205 - 180), (242 - 225)); // v2

    sprites->aliens_t2[0] = select_sprite(sprites->_sheet, 73, 225, (97 - 72), (242 - 225));    // v1
    sprites->aliens_t2[1] = select_sprite(sprites->_sheet, 106, 225, (130 - 105), (242 - 225)); // v2

    sprites->aliens_t3[0] = select_sprite(sprites->_sheet, 35, 225, (60 - 35), (242 - 225)); // v3
    sprites->aliens_t3[1] = select_sprite(sprites->_sheet, 6, 225, (27 - 2), (242 - 225));   // v3
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
    int pos_x = 500;
    int pos_y = 0;
    al_draw_text(font, WHITE, 300, 0, 0, "LIVES ");
    for (int i = 0; i < lives; i++)
    {
        pos_x = pos_x + al_get_bitmap_width(live);
        al_draw_bitmap(live, pos_x, pos_y, 0);
    }
}
