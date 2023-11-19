#include "obstacles.h"
#include "utils.h"


/* Inicializa obstáculos */
void init_obstacles(OBSTACLE obstacles[NUM_OBSTACLES], SPRITES *sprites)
{
    int pos_y = TOTAL_HEIGHT - 3 * MARGIN;

    for (int i = 0; i < NUM_OBSTACLES; i++)
    {
        if (i == 0)
            obstacles[i].x = MARGIN;
        else
            obstacles[i].x = obstacles[i - 1].x + obstacles[i - 1].w + OBSTACLE_SPACING;
        obstacles[i].y = pos_y;
        obstacles[i].life = OBSTACLE_LIFE;
        obstacles[i].w = al_get_bitmap_width(sprites->obstacles[0]);
        obstacles[i].h = al_get_bitmap_height(sprites->obstacles[0]);
    }
}

bool obstacle_collision(OBSTACLE obstacles[NUM_OBSTACLES], SHOT shot, int enemy_type)
{
    for (int i = 0; i < NUM_OBSTACLES; i++)
    {
        if ((obstacles[i].state != DEAD_OBSTACLE) &&
            (shot.x >= obstacles[i].x) &&
            (shot.x <= (obstacles[i].x + obstacles[i].w * OBSTACLE_RESIZE)) &&
            (shot.y >= obstacles[i].y) &&
            (shot.y <= (obstacles[i].y + obstacles[i].h * OBSTACLE_RESIZE)))
        {
            if (enemy_type == weak || enemy_type == 0)
                obstacles[i].life--;
            else
                obstacles[i].life -= 2;

            if (obstacles[i].life <= 0)
            {
                obstacles[i].state = DEAD_OBSTACLE;
                obstacles[i].life = 0;
            }

            return true; // Colisão detectada
        }
    }

    return false; // Sem colisão
}

/* Desenha obstáculos */
void draw_obstacles(OBSTACLE obstacles[NUM_OBSTACLES], SPRITES *sprites)
{
    ALLEGRO_FONT *font = al_load_font("./assets/VT323-Regular.ttf", 48, 0);
    must_init(font, "font");
    for (int i = 0; i < NUM_OBSTACLES; i++)
    {
        if (obstacles[i].state != DEAD_OBSTACLE)
        {
            if (obstacles[i].life <= 2)
                scale_image(sprites->obstacles[4], obstacles[i].x, obstacles[i].y, OBSTACLE_RESIZE);
            else if (obstacles[i].life <= 4)
                scale_image(sprites->obstacles[3], obstacles[i].x, obstacles[i].y, OBSTACLE_RESIZE);
            else if (obstacles[i].life <= 6)
                scale_image(sprites->obstacles[2], obstacles[i].x, obstacles[i].y, OBSTACLE_RESIZE);
            else if (obstacles[i].life <= 8)
                scale_image(sprites->obstacles[2], obstacles[i].x, obstacles[i].y, OBSTACLE_RESIZE);
            else if (obstacles[i].life > 0)
                scale_image(sprites->obstacles[0], obstacles[i].x, obstacles[i].y, OBSTACLE_RESIZE);

            al_draw_textf(font, WHITE, obstacles[i].x, obstacles[i].y, 0, "%d", obstacles[i].life);
        }
    }
}