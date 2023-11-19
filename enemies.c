
#include "display.h"
#include "player.h"
#include "enemies.h"
#include "shots.h"
#include "utils.h"
#include <time.h>

/* Retorna falso se algum inimigo estiver vivo */
bool checkAllEnemiesDefeated(ENEMY (*enemies)[ENEMIES_PER_LINE])
{
    for (int i = 0; i < NUM_ENEMIES_LINES; i++)
    {
        for (int j = 0; j < ENEMIES_PER_LINE; j++)
        {
            if (enemies[i][j].state != DEAD_ENEMY)
            {
                return false;
            }
        }
    }
    return true;
}

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
    float height = 2 * MARGIN;
    for (int i = 0; i < NUM_ENEMIES_LINES; i++)
    {
        int type = get_enemy_type(i);
        for (int j = 0; j < ENEMIES_PER_LINE; j++)
        {
            enemies[i][j].direction = LEFT;
            enemies[i][j].type = type;
            enemies[i][j].state = ENEMY_STATE_ONE;

            if (((i == 0) && (j == 0)) | (j == 0))
                enemies[i][j].x = 0;
            else
                enemies[i][j].x = enemies[i][j - 1].x + (enemies[i][j - 1].width * ENEMY_RESIZE) + ENEMY_SPACING;

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

/* Libera memória */
void destroy_enemies(ENEMY (*enemies)[ENEMIES_PER_LINE])
{
    for (int i = 0; i < NUM_ENEMIES_LINES; i++)
    {
        for (int j = 0; j < ENEMIES_PER_LINE; j++)
        {
            SHOT *aux;
            aux = enemies[i][j].shots;
            enemies[i][j].shots = NULL;
            free(aux);
        }
    }
}

/* Desenha tiros inimigos */
void draw_enemies_shots(ENEMY enemy, SPRITES *sprites)
{
    if (enemy.shots != NULL)
    {
        if (enemy.type == weak)
        {
            if (enemy.shots->state == SHOT_STATE_ONE)
                al_draw_filled_rectangle(enemy.shots->x, enemy.shots->y, enemy.shots->x + 5, enemy.shots->y + 20, WHITE);
            else if (enemy.shots->state == SHOT_STATE_TWO)
                al_draw_filled_rectangle(enemy.shots->x, enemy.shots->y, enemy.shots->x + 5, enemy.shots->y + 20, GREEN);
        }
        else if (enemy.type == intermed)
        {
            if (enemy.shots->state == SHOT_STATE_ONE)
                scale_image(sprites->shot_intermed, enemy.shots->x, enemy.shots->y, 2);
            else if (enemy.shots->state == SHOT_STATE_TWO)
                al_draw_scaled_bitmap(sprites->shot_intermed, 0, 0,
                                      al_get_bitmap_width(sprites->shot_intermed),
                                      al_get_bitmap_height(sprites->shot_intermed),
                                      enemy.shots->x, enemy.shots->y,
                                      al_get_bitmap_width(sprites->shot_intermed) * 2,
                                      -al_get_bitmap_height(sprites->shot_intermed) * 2, 0);
        }
        else if (enemy.type == strong)
        {
            if (enemy.shots->state == SHOT_STATE_ONE)
                scale_image(sprites->shot_strong, enemy.shots->x, enemy.shots->y, 1);
            else if (enemy.shots->state == SHOT_STATE_TWO)
                al_draw_bitmap(sprites->shot_strong, enemy.shots->x, enemy.shots->y, ALLEGRO_FLIP_HORIZONTAL);
        }
    }
}

/* Desenha inimigos */
void draw_enemies(ENEMY enemies[NUM_ENEMIES_LINES][ENEMIES_PER_LINE], SPRITES *sprites)
{
    for (int i = 0; i < NUM_ENEMIES_LINES; i++)
    {
        for (int j = 0; j < ENEMIES_PER_LINE; j++)
        {
            if (enemies[i][j].state != DEAD_ENEMY)
            {
                draw_enemies_shots(enemies[i][j], sprites);

                if (enemies[i][j].type == weak)
                {
                    if (enemies[i][j].state == ENEMY_STATE_ONE)
                        scale_image(sprites->aliens_t1[0], enemies[i][j].x, enemies[i][j].y, ENEMY_RESIZE);

                    else if (enemies[i][j].state == ENEMY_STATE_TWO)
                        scale_image(sprites->aliens_t1[1], enemies[i][j].x, enemies[i][j].y, ENEMY_RESIZE);
                }
                else if (enemies[i][j].type == intermed)
                {
                    if (enemies[i][j].state == ENEMY_STATE_ONE)
                        scale_image(sprites->aliens_t2[0], enemies[i][j].x, enemies[i][j].y, ENEMY_RESIZE);

                    else if (enemies[i][j].state == ENEMY_STATE_TWO)
                        scale_image(sprites->aliens_t2[1], enemies[i][j].x, enemies[i][j].y, ENEMY_RESIZE);
                }
                else
                {
                    if (enemies[i][j].state == ENEMY_STATE_ONE)
                        scale_image(sprites->aliens_t3[0], enemies[i][j].x, enemies[i][j].y, ENEMY_RESIZE);

                    else if (enemies[i][j].state == ENEMY_STATE_TWO)
                        scale_image(sprites->aliens_t3[1], enemies[i][j].x, enemies[i][j].y, ENEMY_RESIZE);
                }
            }
        }
    }
}

/* Inicializa nave vermelha */
void init_spaceship(ENEMY *spaceship, SPRITES *sprites)
{
    spaceship->x = 0;
    spaceship->y = MARGIN;
    spaceship->width = al_get_bitmap_width(sprites->spaceship) * 0.5;
    spaceship->height = al_get_bitmap_height(sprites->spaceship) * 0.5;
    spaceship->direction = RIGHT;
    spaceship->shots = NULL;
}

/* Movimenta inimigos */
void move_enemies(ENEMY (*enemies)[ENEMIES_PER_LINE])
{
    /* Muda a linha dos inimigos quando necessário */
    for (int i = 0; i < NUM_ENEMIES_LINES; i++)
    {
        for (int j = 0; j < ENEMIES_PER_LINE; j++)
        {
            if (enemies[i][j].state != DEAD_ENEMY)
                enemies[i][j].state = !enemies[i][j].state;

            if ((enemies[i][j].x >= TOTAL_WIDTH - enemies[i][j].width * ENEMY_RESIZE) || (enemies[i][j].x < 0)) // encosta na borda

                for (int i = 0; i < NUM_ENEMIES_LINES; i++)

                    for (int j = 0; j < ENEMIES_PER_LINE; j++)
                    {
                        enemies[i][j].y += ENEMY_SPEED / 6;
                        enemies[i][j].direction = !enemies[i][j].direction; // inverte a direção
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

/* Atualiza posição de inimigos e seus tiros */
void update_enemies(ENEMY (*enemies)[ENEMIES_PER_LINE], ENEMY *spaceship)
{
    move_red_spaceship(spaceship);
    move_enemies(enemies);
}
