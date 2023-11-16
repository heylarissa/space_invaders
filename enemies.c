#include "game.h"
#include "shots.h"
#include "enemies.h"
#include "player.h"
#include "display.h"

void init_enemies(ENEMY *enemy)
{
    enemy->size = SIZE_PLAYER;
    enemy->next = NULL;
    enemy->x = MARGIN;
    enemy->y = 2 * MARGIN - SIZE_PLAYER + 20;
}

void init_spaceship(ENEMY *spaceship, SPRITES *sprites)
{
    spaceship->x = 0;
    spaceship->y = MARGIN;
    spaceship->size = al_get_bitmap_width(sprites->spaceship) * 0.5;
}

void init_game(PLAYER *player, ENEMY *enemies, ENEMY *spaceship, SPRITES *sprites)
{
    init_sprites(sprites);
    init_player(player, sprites);
    init_spaceship(spaceship, sprites);
    init_enemies(enemies);
}

void update_enemies(ENEMY *enemies, ENEMY *spaceship)
{
    if (spaceship->direction == RIGHT)
    {
        spaceship->x += 15;
    }
    else
    {
        spaceship->x -= 15;
    }

    if ((spaceship->x == TOTAL_WIDTH - spaceship->size) || (spaceship->x == 0))
    {
        spaceship->direction = !spaceship->direction;
    }

    if (enemies->direction == LEFT)
    {
        enemies->x += 10;
    }
    else
    {
        enemies->x -= 10;
    }

    if ((enemies->x == TOTAL_WIDTH - SIZE_PLAYER - MARGIN) || (enemies->x == MARGIN))
    {
        enemies->y += SIZE_PLAYER / 2;
        enemies->direction = !enemies->direction; // inverte a direção
    }
}
