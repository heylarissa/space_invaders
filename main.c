#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <time.h>

#include "shots.h"
#include "display.h"
#include "game.h"
#include "player.h"
#include "enemies.h"
#include "obstacles.h"

void start_new_round(ENEMY (*enemies)[ENEMIES_PER_LINE], ENEMY *spaceship, SPRITES *sprites, PLAYER *player, OBSTACLE obstacles[NUM_OBSTACLES])
{
    init_spaceship(spaceship, sprites);
    init_enemies(sprites, enemies);
    init_obstacles(obstacles, sprites);
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

int main()
{
    // TODO: Refatorar toda a inicialização do allegro para uma única struct
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60.0);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    must_init(queue, "queue");

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    ALLEGRO_DISPLAY *disp = al_create_display(TOTAL_WIDTH, TOTAL_HEIGHT);
    must_init(disp, "display");
    must_init(al_init_font_addon(), "addon de fonte");
    must_init(al_init_ttf_addon(), "addon de fonte ttf");

    ALLEGRO_FONT *font = al_load_font("./assets/VT323-Regular.ttf", 48, 0);
    must_init(font, "font");

    must_init(al_init_primitives_addon(), "primitives");
    must_init(al_init_image_addon(), "image addon");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool done = false;
    bool redraw = true;

    ALLEGRO_EVENT event;
    SPRITES *sprites = (SPRITES *)malloc(sizeof(SPRITES));
    PLAYER player;
    ENEMY spaceship;
    ENEMY enemies[NUM_ENEMIES_LINES][ENEMIES_PER_LINE];
    OBSTACLE obstacles[NUM_OBSTACLES];

    init_game(&player, enemies, &spaceship, sprites, obstacles);

    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));

    int frame_count = 0;

    al_start_timer(timer);
    int currentRound = 1;

    GameState gameState = MENU;

    while (!done)
    {
        al_wait_for_event(queue, &event);

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            if (key[ALLEGRO_KEY_ESCAPE])
                done = true;
            switch (gameState)
            {
            case MENU:
                if ((key[ALLEGRO_KEY_SPACE] || key[ALLEGRO_KEY_ENTER]))
                    gameState = GAME;

                break;
            case PAUSED:
                if (key[ALLEGRO_KEY_P])
                    gameState = GAME;

                break;
            case GAME_OVER:
                if (key[ALLEGRO_KEY_ESCAPE])
                    done = true;
                break;
            case GAME:
                frame_count++;

                if (player.lives == 0)
                    gameState = GAME_OVER;

                if (player.state == explode)
                {
                    player.explosion_frame++;

                    if (player.explosion_frame > MAX_EXPLOSION_FRAMES)
                    {
                        player.state = alive;
                        player.explosion_frame = 0;
                        player.x = 50;
                    }
                }

                /* player logic */
                update_player_shots(&player, enemies, obstacles);

                /* enemy logic */
                if (frame_count % 30 == 0)
                    update_enemies(enemies, &spaceship);
                else if (frame_count % 5 == 0)
                    update_enemies_shots(enemies, &player, obstacles);

                /* interação com teclado */
                if (key[ALLEGRO_KEY_LEFT] && (player.x >= 0))
                    player.x -= PLAYER_SPEED;
                else if (key[ALLEGRO_KEY_RIGHT] && player.x <= (TOTAL_WIDTH - player.w))
                    player.x += PLAYER_SPEED;
                else if (key[ALLEGRO_KEY_SPACE])
                    create_player_shot(&player);

                if (checkAllEnemiesDefeated(enemies))
                {
                    if (player.lives < 5)
                        player.lives++;

                    start_new_round(enemies, &spaceship, sprites, &player, obstacles);
                    currentRound++;
                }
                break;
            }

            for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
                key[i] &= KEY_SEEN;

            redraw = true;
            break;

        case ALLEGRO_EVENT_KEY_DOWN:                               // tecla pressionada
            key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED; // armazena no vetor na posição respectiva ao keycode da tecla

            if (event.keyboard.keycode == ALLEGRO_KEY_P)
            {
                if (gameState == GAME)
                {
                    gameState = PAUSED;
                    al_stop_timer(timer);
                }
                else if (gameState == PAUSED)
                {
                    gameState = GAME;
                    al_start_timer(timer);
                }
            }
            break;

        case ALLEGRO_EVENT_KEY_UP: // tecla liberada
            key[event.keyboard.keycode] &= KEY_RELEASED;
            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        }

        if (done)
            break;

        if (redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(BLACK);
            switch (gameState)
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
                /* desenha obstáculos */
                draw_obstacles(obstacles, sprites);

                // desenha tela
                al_draw_textf(font, WHITE, 0, 0, 0, "SCORE %d", player.score);                                // score do player
                draw_lives(player.lives, sprites->player, font);                                              // vidas do player
                al_draw_textf(font, WHITE, 800, 0, 0, "ROUND %d", currentRound);                              // score do player
                al_draw_line(0, TOTAL_HEIGHT - MARGIN / 2, TOTAL_WIDTH, TOTAL_HEIGHT - MARGIN / 2, GREEN, 5); // margem verde inferior

                // desenha inimigos
                al_draw_scaled_bitmap(sprites->spaceship, 0, 0,
                                      al_get_bitmap_width(sprites->spaceship),
                                      al_get_bitmap_height(sprites->spaceship),
                                      spaceship.x, spaceship.y,
                                      al_get_bitmap_width(sprites->spaceship) * 0.5,
                                      al_get_bitmap_height(sprites->spaceship) * 0.5, 0); // desenha nave vermelha

                draw_enemies(enemies, sprites);

                // desenha player
                draw_player(sprites, player);

                break;
            }
            al_flip_display();

            redraw = false;
        }
    }

    destroy_enemies(enemies);
    destroy_player(&player);
    destroy_sprites(sprites);
    al_destroy_font(font);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_display(disp);

    return 0;
}