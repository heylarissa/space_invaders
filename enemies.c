
#include "display.h"
#include "game.h"
#include "player.h"
#include "enemies.h"
#include "shots.h"
#include "utils.h"

int get_enemy_type(int line)
{
    int type;

    if (line == 0)
        type = 3; // strong
    else if (line == 1 || line == 2)
        type = 2; // intermediate
    else
        type = 1; // weak

    return type;
}

ENEMY *init_enemies(SPRITES *sprites)
{
    ENEMY *enemies = NULL;
    ENEMY *prev = NULL;
    float height = 2 * MARGIN - SIZE_ENEMY + 20;
    for (int line = 0; line < NUM_ENEMIES_LINES; line++)
    {
        int type = get_enemy_type(line);

        for (int i = 0; i < ENEMIES_PER_LINE; i++)
        {
            ENEMY *new_enemy = malloc(sizeof(ENEMY));
            if (new_enemy == NULL)
            {
                fprintf(stderr, "Erro ao alocar memória para inimigo.\n");
                exit(EXIT_FAILURE);
            }

            new_enemy->direction = LEFT;
            new_enemy->next = NULL;
            new_enemy->type = type;
            new_enemy->state = ENEMY_STATE_ONE; // define a imagem a exibir do inimigo

            if (prev != NULL)
                new_enemy->x = prev->x + SIZE_ENEMY + ENEMY_SPACING; // define a posição inicial
            else
                new_enemy->x = 0; // Valor inicial se prev for NULL

            new_enemy->alive = TRUE;
            new_enemy->line = line;
            new_enemy->shots = NULL;

            // define o tamanho do bloco do inimigo
            if (new_enemy->type == 1)
            {
                new_enemy->width = al_get_bitmap_width(sprites->aliens_t1[0]);
                new_enemy->height = al_get_bitmap_height(sprites->aliens_t1[0]);
            }

            else if (new_enemy->type == 2)
            {
                new_enemy->width = al_get_bitmap_width(sprites->aliens_t2[0]);
                new_enemy->height = al_get_bitmap_height(sprites->aliens_t2[0]);
            }
            else
            {
                new_enemy->width = al_get_bitmap_width(sprites->aliens_t3[0]);
                new_enemy->height = al_get_bitmap_height(sprites->aliens_t2[0]);
            }
            new_enemy->y = height;

            // Adiciona o novo inimigo à lista
            if (enemies == NULL)
                enemies = new_enemy;
            else
            {
                new_enemy->next = enemies;
                enemies = new_enemy;
            }

            prev = new_enemy;
        }
        prev = NULL;
        height = height + ENEMY_SPACING;
    }
    return enemies;
}

void draw_enemies(ENEMY *enemies, SPRITES *sprites)
{
    ENEMY *aux;
    aux = enemies;
    for (int i = 0; i < (ENEMIES_PER_LINE * NUM_ENEMIES_LINES); i++)
    {
        if (aux->state != DEAD_ENEMY)
        {
            if (aux->type == 1)
            {
                if (aux->state == ENEMY_STATE_ONE)
                    scale_image(sprites->aliens_t1[0], aux->x, aux->y, 2);
                else if (aux->state == ENEMY_STATE_TWO)
                    scale_image(sprites->aliens_t1[1], aux->x, aux->y, 2);
            }
            else if (aux->type == 2)
            {
                if (aux->state == ENEMY_STATE_ONE)
                    scale_image(sprites->aliens_t2[0], aux->x, aux->y, 2);
                else if (aux->state == ENEMY_STATE_TWO)
                    scale_image(sprites->aliens_t2[1], aux->x, aux->y, 2);
            }
            else
            {
                if (aux->state == ENEMY_STATE_ONE)
                    scale_image(sprites->aliens_t3[0], aux->x, aux->y, 2);
                else if (aux->state == ENEMY_STATE_TWO)
                    scale_image(sprites->aliens_t3[1], aux->x, aux->y, 2);
            }
        }

        aux = aux->next;
    }
}

void init_spaceship(ENEMY *spaceship, SPRITES *sprites)
{
    spaceship->x = 0;
    spaceship->y = MARGIN;
    spaceship->width = al_get_bitmap_width(sprites->spaceship) * 0.5;
    spaceship->height = al_get_bitmap_height(sprites->spaceship) * 0.5;

    spaceship->next = NULL;
    spaceship->direction = RIGHT;
}

void update_enemies(ENEMY *enemies, ENEMY *spaceship)
{
    if (spaceship->direction == RIGHT)
    {
        spaceship->x += 2 * ENEMY_SPEED;
    }
    else
    {
        spaceship->x -= 2 * ENEMY_SPEED;
    }

    if ((spaceship->x == TOTAL_WIDTH - spaceship->width) || (spaceship->x == 0))
    {
        spaceship->direction = !spaceship->direction;
    }

    ENEMY *aux;
    aux = enemies;
    while (aux != NULL)
    {
        aux->state = !aux->state;
        if (aux->direction == LEFT)
        {
            aux->x += ENEMY_SPEED;
        }
        else
        {
            aux->x -= ENEMY_SPEED;
        }

        if ((aux->x >= TOTAL_WIDTH - aux->width) || (aux->x <= 0)) // encosta na borda
        {
            ENEMY *temp;
            temp = enemies;

            while (temp != NULL)
            {
                temp->y += 2 * ENEMY_SPEED;
                temp->direction = !temp->direction; // inverte a direção

                temp = temp->next;
            }
        }

        aux = aux->next;
    }
}
