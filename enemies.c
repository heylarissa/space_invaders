
#include "display.h"
#include "game.h"
#include "player.h"
#include "enemies.h"
#include "shots.h"

void create_enemy(ENEMY *enemies, ENEMY *new)
{
}

int get_enemy_type(int line)
{
    int type;
    if (line == 0)
    {
        type = 3; // strong
    }
    else if (line == 1 || line == 2)
    {
        type = 2; // intermediate
    }
    else
    {
        type = 1; // weak
    }

    return type;
}

ENEMY *init_enemies()
{
    ENEMY *enemies = NULL;
    ENEMY *prev = NULL;
    float height = 2 * MARGIN - SIZE_PLAYER + 20;
    for (int line = 0; line < NUM_ENEMIES_LINES; line++)
    {
        int type = get_enemy_type(line);

        for (int i = 0; i < ENEMIES_PER_LINE; i++)
        {
            ENEMY *new_enemy = malloc(sizeof(ENEMY));
            if (new_enemy == NULL)
            {
                // Lidar com erro de alocação de memória, se necessário
                fprintf(stderr, "Erro ao alocar memória para inimigo.\n");
                exit(EXIT_FAILURE);
            }

            new_enemy->direction = LEFT;
            new_enemy->next = NULL;
            new_enemy->type = type;
            new_enemy->state = ENEMY_STATE_ONE; // define a imagem a exibir do inimigo

            // define a posição inicial
            // Se prev não for NULL, usa a posição x do inimigo anterior
            if (prev != NULL)
                new_enemy->x = prev->x + SIZE_ENEMY + ENEMY_SPACING;
            else
                new_enemy->x = MARGIN; // Valor inicial se prev for NULL

            new_enemy->alive = TRUE;
            new_enemy->line = line;
            new_enemy->shots = NULL;
            new_enemy->size = SIZE_ENEMY;
            new_enemy->y = height;

            // Adiciona o novo inimigo à lista
            if (enemies == NULL)
            {
                enemies = new_enemy;
            }
            else
            {
                new_enemy->next = enemies;
                enemies = new_enemy;
            }

            prev = new_enemy;
        }

        height = height + 50;
    }
    return enemies;
    // enemies->direction = LEFT;
    // enemies->size = SIZE_PLAYER;
    // enemies->next = NULL;
    // enemies->x = MARGIN;
    // enemies->y = 2 * MARGIN - SIZE_PLAYER + 20;
}

void init_spaceship(ENEMY *spaceship, SPRITES *sprites)
{
    spaceship->x = 0;
    spaceship->y = MARGIN;
    spaceship->size = al_get_bitmap_width(sprites->spaceship) * 0.5;
    spaceship->next = NULL;
    spaceship->direction = RIGHT;
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
