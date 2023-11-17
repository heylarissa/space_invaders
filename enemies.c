
#include "display.h"
#include "game.h"
#include "player.h"
#include "enemies.h"
#include "shots.h"
#include "utils.h"
#include <time.h>

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

void draw_enemies_shots(SHOT *shot_aux)
{
    if (shot_aux != NULL)
        al_draw_filled_rectangle(shot_aux->x, shot_aux->y, shot_aux->x - 5, shot_aux->y - 20, WHITE);
}
void draw_enemies(ENEMY *enemies, SPRITES *sprites)
{
    ENEMY *aux;
    aux = enemies;
    while (aux != NULL)
    {
        draw_enemies_shots(aux->shots);
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

void move_enemies(ENEMY *enemies)
{
    ENEMY *aux = enemies;

    /* Muda a linha dos inimigos quando necessário */
    while (aux != NULL)
    {
        aux->state = !aux->state;

        if ((aux->x >= TOTAL_WIDTH - aux->width) || (aux->x < 0)) // encosta na borda
        {
            ENEMY *temp = enemies;
            while (temp != NULL)
            {
                temp->y += ENEMY_SPEED / 3;
                temp->direction = !temp->direction; // inverte a direção

                temp = temp->next;
            }
        }

        aux = aux->next;
    }

    /* Atualiza o local dos inimigos */
    aux = enemies;
    while (aux != NULL)
    {
        if (aux->direction == LEFT)
        {
            aux->x += ENEMY_SPEED;
        }
        else
        {
            aux->x -= ENEMY_SPEED;
        }

        aux = aux->next;
    }
}

/* Atualiza nave vermelha inimiga */
void move_red_spaceship(ENEMY *spaceship)
{
    if (spaceship->direction == RIGHT)
    {
        spaceship->x += 3 * ENEMY_SPEED;
    }
    else
    {
        spaceship->x -= 3 * ENEMY_SPEED;
    }

    if ((spaceship->x >= TOTAL_WIDTH - spaceship->width) || (spaceship->x <= 0))
    {
        spaceship->direction = !spaceship->direction;
    }
}

/* Cria o tiro do inimigo */
void set_shooting_ability(ENEMY *enemies, int chosen)
{
    int i;

    ENEMY *aux;

    aux = enemies;
    i = 0;

    while (aux != NULL && i != chosen) // vai até o final da lista ou até encontrar o indice
    {
        aux = aux->next;
    }

    if (aux != NULL && aux->shots == NULL)
    {
        // Cria tiro inimigo
        aux->shots = malloc(sizeof(SHOT));
        aux->shots->direction = DOWN;
        aux->shots->next = NULL;
        aux->shots->x = aux->x + aux->width / 2; // atira a partir do meio do inimigo
        aux->shots->y = aux->y;
    }
}

/* Retorna TRUE se o indice já tiver sido escolhido*/
int contains(int chosen[2], int index)
{
    if (chosen[0] == index || chosen[1] == index)
        return TRUE;

    return FALSE;
}

/* Escolhe quais inimigos irão atirar */
void choose_shoot_enemies(ENEMY *enemies)
{
    int total_enemies = ENEMIES_PER_LINE * NUM_ENEMIES_LINES;

    int chosen[2];
    srand((unsigned int)time(NULL));

    // Escolhe aleatoriamente os índices dos inimigos que atirarão
    for (int i = 0; i < 2; i++)
    {
        int randomIndex;

        // Garante que o índice escolhido seja único
        do
        {
            randomIndex = rand() % total_enemies;
        } while (contains(chosen, randomIndex));

        // Adiciona o índice escolhido à lista vinculada
        chosen[i] = randomIndex;

        // Define a capacidade de atirar para verdadeiro no inimigo correspondente
        set_shooting_ability(enemies, chosen[i]);
    }
}

/* Retorna se existem tiros ativos na lista de inimigos */
int no_enemy_active_shot(ENEMY *enemies)
{
    ENEMY *aux;
    aux = enemies;

    while (aux != NULL)
    {
        if (aux->shots != NULL)
        {
            return FALSE;
        }
        aux = aux->next;
    }

    return TRUE;
}

/* Atualiza posição dos tiros inimigos */
void update_enemies_shots(ENEMY *enemies)
{
    ENEMY *aux;
    aux = enemies;

    while (aux != NULL)
    {
        if (aux->shots != NULL)
        {
            aux->shots->y += aux->height;
            //           if (check_collision(aux->shots->x, aux->shots->y, ENEMY_SHOT_SIZE, ENEMY_SHOT_SIZE, player->x, player->y, SIZE_PLAYER, SIZE_PLAYER))
            // {
            //     // Trata a colisão com o jogador
            //     // ... (coloque aqui o código para tratar a colisão do tiro inimigo com o jogador)
            // }

            if (aux->shots->y >= TOTAL_HEIGHT)
                aux->shots = NULL;
        }

        aux = aux->next;
    }

    if (no_enemy_active_shot(enemies))
        choose_shoot_enemies(enemies);
}

/* Atualiza posição de inimigos e seus tiros */
void update_enemies(ENEMY *enemies, ENEMY *spaceship)
{
    move_red_spaceship(spaceship);
    move_enemies(enemies);
}
