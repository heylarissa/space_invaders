
#include "display.h"
#include "game.h"
#include "player.h"
#include "enemies.h"
#include "shots.h"
#include "utils.h"
#include <time.h>

/* Retorna o tipo do inimigo com base na linha em que ele está */
int get_enemy_type(int line)
{
    int type;

    if (line == 0)
        type = strong;
    else if (line == 1 || line == 2)
        type = intermed;
    else
        type = weak;

    return type;
}

/* Inicializa os inimigos para início do jogo */
void init_enemies(SPRITES *sprites, ENEMY (*enemies)[ENEMIES_PER_LINE])
{

    float height = 2 * MARGIN - SIZE_ENEMY + 20;
    for (int i = 0; i < NUM_ENEMIES_LINES; i++)
    {
        int type = get_enemy_type(i);
        for (int j = 0; j < ENEMIES_PER_LINE; j++)
        {
            enemies[i][j].direction = LEFT;
            enemies[i][j].type = type;
            enemies[i][j].state = ENEMY_STATE_ONE; // define a imagem a exibir do inimigo

            if (((i == 0) && (j == 0)) | (j == 0))
                enemies[i][j].x = 0;
            else
                enemies[i][j].x = enemies[i][j - 1].x + SIZE_ENEMY + ENEMY_SPACING;

            enemies[i][j].shots = NULL;

            // define o tamanho do bloco do inimigo
            if (enemies[i][j].type == weak)
            {
                enemies[i][j].width = al_get_bitmap_width(sprites->aliens_t1[0]);
                enemies[i][j].height = al_get_bitmap_height(sprites->aliens_t1[0]);
            }

            else if (enemies[i][j].type == intermed)
            {
                enemies[i][j].width = al_get_bitmap_width(sprites->aliens_t2[0]);
                enemies[i][j].height = al_get_bitmap_height(sprites->aliens_t2[0]);
            }
            else if (enemies[i][j].type == strong)
            {
                enemies[i][j].width = al_get_bitmap_width(sprites->aliens_t3[0]);
                enemies[i][j].height = al_get_bitmap_height(sprites->aliens_t2[0]);
            }
            enemies[i][j].y = height;
        }
        height = height + ENEMY_SPACING;
    }
}

void draw_enemies_shots(SHOT *shot_aux)
{
    if (shot_aux != NULL)
        al_draw_filled_rectangle(shot_aux->x, shot_aux->y, shot_aux->x - 5, shot_aux->y - 20, WHITE);
}

void draw_enemies(ENEMY enemies[NUM_ENEMIES_LINES][ENEMIES_PER_LINE], SPRITES *sprites)
{

    ALLEGRO_FONT *font = al_load_font("./assets/VT323-Regular.ttf", 48, 0);
    must_init(font, "font");

    scale_image(sprites->aliens_t1[0], enemies[0][1].x, enemies[0][1].y, 2);

    for (int i = 0; i < NUM_ENEMIES_LINES; i++)
    {
        for (int j = 0; j < ENEMIES_PER_LINE; j++)
        {
            if (enemies[i][j].state != DEAD_ENEMY)
            {
                if (enemies[i][j].type == weak)
                {
                    if (enemies[i][j].state == ENEMY_STATE_ONE)
                        scale_image(sprites->aliens_t1[0], enemies[i][j].x, enemies[i][j].y, 2);

                    else if (enemies[i][j].state == ENEMY_STATE_TWO)
                        scale_image(sprites->aliens_t1[1], enemies[i][j].x, enemies[i][j].y, 2);
                }

                else if (enemies[i][j].type == intermed)
                {
                    if (enemies[i][j].state == ENEMY_STATE_ONE)
                        scale_image(sprites->aliens_t2[0], enemies[i][j].x, enemies[i][j].y, 2);

                    else if (enemies[i][j].state == ENEMY_STATE_TWO)
                        scale_image(sprites->aliens_t2[1], enemies[i][j].x, enemies[i][j].y, 2);
                }
                else
                {
                    if (enemies[i][j].state == ENEMY_STATE_ONE)
                        scale_image(sprites->aliens_t3[0], enemies[i][j].x, enemies[i][j].y, 2);

                    else if (enemies[i][j].state == ENEMY_STATE_TWO)
                        scale_image(sprites->aliens_t3[1], enemies[i][j].x, enemies[i][j].y, 2);
                }
            }
        }
    }
}

void init_spaceship(ENEMY *spaceship, SPRITES *sprites)
{
    spaceship->x = 0;
    spaceship->y = MARGIN;
    spaceship->width = al_get_bitmap_width(sprites->spaceship) * 0.5;
    spaceship->height = al_get_bitmap_height(sprites->spaceship) * 0.5;
    spaceship->direction = RIGHT;
}

void move_enemies(ENEMY (*enemies)[ENEMIES_PER_LINE])
{
    /* Muda a linha dos inimigos quando necessário */

    for (int i = 0; i < NUM_ENEMIES_LINES; i++)
    {
        for (int j = 0; j < ENEMIES_PER_LINE; j++)
        {
            enemies[i][j].state = !enemies[i][j].state;

            if ((enemies[i][j].x >= TOTAL_WIDTH - enemies[i][j].width) || (enemies[i][j].x < 0)) // encosta na borda
            {
                for (int i = 0; i < NUM_ENEMIES_LINES; i++)
                {
                    for (int j = 0; j < ENEMIES_PER_LINE; j++)
                    {
                        enemies[i][j].y += ENEMY_SPEED / 6;
                        enemies[i][j].direction = !enemies[i][j].direction; // inverte a direção
                    }
                }
            }
        }
    }

    /* Movimenta inimigos */
    for (int i = 0; i < NUM_ENEMIES_LINES; i++)
    {
        for (int j = 0; j < ENEMIES_PER_LINE; j++)
        {

            if (enemies[i][j].direction == LEFT)
                enemies[i][j].x += ENEMY_SPEED;
            else
                enemies[i][j].x -= ENEMY_SPEED;
        }
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

/* Escolhe quais inimigos irão atirar */
void choose_shoot_enemies(ENEMY *enemies)
{
    // int total_enemies = ENEMIES_PER_LINE * NUM_ENEMIES_LINES;

    // int chosen[2];
    // srand((unsigned int)time(NULL));

    // // Escolhe aleatoriamente os índices dos inimigos que atirarão
    // for (int i = 0; i < 2; i++)
    // {
    //     int randomIndex;

    //     // Garante que o índice escolhido seja único
    //     do
    //     {
    //         randomIndex = rand() % total_enemies;
    //     } while (contains(chosen, randomIndex));

    //     // Adiciona o índice escolhido à lista vinculada
    //     chosen[i] = randomIndex;

    //     // Define a capacidade de atirar para verdadeiro no inimigo correspondente
    //     set_shooting_ability(enemies, chosen[i]);
    // }
}

/* Retorna se existem tiros ativos na lista de inimigos */
int no_enemy_active_shot(ENEMY *enemies)
{
    // ENEMY *aux;
    // aux = enemies;

    // while (aux != NULL)
    // {
    //     if (aux->shots != NULL)
    //     {
    //         return FALSE;
    //     }
    //     aux = aux->next;
    // }

    return TRUE;
}

/* Atualiza posição dos tiros inimigos */
void update_enemies_shots(ENEMY *enemies)
{
    // ENEMY *aux;
    // aux = enemies;

    // while (aux != NULL)
    // {
    //     if (aux->shots != NULL)
    //     {
    //         aux->shots->y += aux->height;
    //         //           if (check_collision(aux->shots->x, aux->shots->y, ENEMY_SHOT_SIZE, ENEMY_SHOT_SIZE, player->x, player->y, SIZE_PLAYER, SIZE_PLAYER))
    //         // {
    //         //     // Trata a colisão com o jogador
    //         //     // ... (coloque aqui o código para tratar a colisão do tiro inimigo com o jogador)
    //         // }

    //         if (aux->shots->y >= TOTAL_HEIGHT)
    //             aux->shots = NULL;
    //     }

    //     aux = aux->next;
    // }

    // if (no_enemy_active_shot(enemies))
    //     choose_shoot_enemies(enemies);
}

/* Atualiza posição de inimigos e seus tiros */
void update_enemies(ENEMY (*enemies)[ENEMIES_PER_LINE], ENEMY *spaceship)
{
    move_red_spaceship(spaceship);
    move_enemies(enemies);
}
