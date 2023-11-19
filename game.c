#include "game.h"

void start_new_round(ENEMY (*enemies)[ENEMIES_PER_LINE], ENEMY *spaceship, SPRITES *sprites, PLAYER *player, OBSTACLE obstacles[NUM_OBSTACLES])
{
    init_spaceship(spaceship, sprites);
    init_enemies(sprites, enemies);
    init_obstacles(obstacles, sprites);
}

void destroy_game(ENEMY (*enemies)[ENEMIES_PER_LINE], PLAYER *player,
                  SPRITES *sprites, ALLEGRO_FONT *font, ALLEGRO_TIMER *timer,
                  ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_DISPLAY *disp)
{
    destroy_enemies(enemies);
    destroy_player(player);
    destroy_sprites(sprites);
    al_destroy_font(font);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_display(disp);
}

void init_game(PLAYER *player, ENEMY (*enemies)[ENEMIES_PER_LINE], ENEMY *spaceship, SPRITES *sprites, OBSTACLE obstacles[NUM_OBSTACLES])
{
    srand((unsigned int)time(NULL));
    init_sprites(sprites);
    init_player(player, sprites);
    init_spaceship(spaceship, sprites);
    init_enemies(sprites, enemies);
    init_obstacles(obstacles, sprites);
}

void draw_game(OBSTACLE obstacles[NUM_OBSTACLES], SPRITES *sprites, ALLEGRO_FONT *font, PLAYER *player, int currentRound, ENEMY (*enemies)[ENEMIES_PER_LINE], ENEMY spaceship)
{
    /* desenha obstáculos */
    draw_obstacles(obstacles, sprites);

    // desenha tela
    al_draw_textf(font, WHITE, 0, 0, 0, "SCORE %d", player->score);                               // score do player
    draw_lives(player->lives, sprites->player, font);                                             // vidas do player
    al_draw_textf(font, WHITE, 800, 0, 0, "ROUND %d", currentRound);                              // score do player
    al_draw_line(0, TOTAL_HEIGHT - MARGIN / 2, TOTAL_WIDTH, TOTAL_HEIGHT - MARGIN / 2, GREEN, 5); // margem verde inferior

    // desenha inimigos
    draw_red_spaceship(sprites, spaceship);

    draw_enemies(enemies, sprites);

    // desenha player
    draw_player(sprites, *player);
}
void game_logic(unsigned char key[], PLAYER *player, GameState *gameState, int *frame_count, SPRITES *sprites, ENEMY *spaceship, ENEMY (*enemies)[ENEMIES_PER_LINE], OBSTACLE obstacles[NUM_OBSTACLES])
{
    if (player->lives == 0)
        *gameState = GAME_OVER;

    if (player->state == explode)
    {
        player->state = alive;
        player->x = 50;
    }

    /* enemy logic */
    if (*frame_count % 30 == 0)
        update_enemies(enemies, spaceship);
    else if (*frame_count % 5 == 0)
        update_enemies_shots(enemies, player, obstacles);

    /* player logic */
    update_player_shots(player, enemies, obstacles, spaceship);
    move_player(key, player);
}
void redraw_screem(GameState *gameState, SPRITES *sprites, ALLEGRO_FONT *font, int currentRound, OBSTACLE obstacles[NUM_OBSTACLES], PLAYER *player, ENEMY (*enemies)[ENEMIES_PER_LINE], ENEMY spaceship)
{
    switch (*gameState)
    {
    case MENU:
        al_draw_bitmap(sprites->spaceinvaderslogo, (TOTAL_WIDTH) / 2 - (410 - 160) / 2, (TOTAL_HEIGHT) / 2 - 2 * MARGIN, 0);
        al_draw_textf(font, WHITE, (TOTAL_WIDTH) / 2, MARGIN, ALLEGRO_ALIGN_CENTER, "MENU");
        al_draw_textf(font, GREEN, (TOTAL_WIDTH) / 2, (TOTAL_HEIGHT) / 2, ALLEGRO_ALIGN_CENTER, "PRESS SPACE OR ENTER TO START");
        break;

    case GAME_OVER:
        al_draw_bitmap(sprites->spaceinvaderslogo, (TOTAL_WIDTH) / 2 - (410 - 160) / 2, (TOTAL_HEIGHT) / 2 - 2 * MARGIN, 0);
        al_draw_textf(font, WHITE, (TOTAL_WIDTH) / 2, MARGIN, ALLEGRO_ALIGN_CENTER, "GAME OVER");
        al_draw_textf(font, GREEN, (TOTAL_WIDTH) / 2, (TOTAL_HEIGHT) / 2, ALLEGRO_ALIGN_CENTER, "PRESS ESC OR CLOSE THE WINDOW");
        break;

    case PAUSED:
        al_draw_bitmap(sprites->spaceinvaderslogo, (TOTAL_WIDTH) / 2 - (410 - 160) / 2, (TOTAL_HEIGHT) / 2 - 2 * MARGIN, 0);
        al_draw_textf(font, WHITE, (TOTAL_WIDTH) / 2, MARGIN, ALLEGRO_ALIGN_CENTER, "PAUSED");
        al_draw_textf(font, GREEN, (TOTAL_WIDTH) / 2, (TOTAL_HEIGHT) / 2, ALLEGRO_ALIGN_CENTER, "PRESS P TO CONTINUE");
        al_flip_display();
        break;

    case GAME:

        draw_game(obstacles, sprites, font, player, currentRound, enemies, spaceship);
        break;
    }
}