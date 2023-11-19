#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <time.h>

#include "display.h"
#include "game.h"
#include "shots.h"
#include "player.h"
#include "enemies.h"
#include "obstacles.h"

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
                game_logic(key, &player, &gameState, &frame_count, sprites, &spaceship, enemies, obstacles);
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

            if (event.keyboard.keycode == ALLEGRO_KEY_P) // pause
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
            redraw_screem(&gameState, sprites, font, currentRound, obstacles, &player, enemies, spaceship);
            al_flip_display();

            redraw = false;
        }
    }

    destroy_game(enemies, &player, sprites, font, timer, queue, disp);

    return 0;
}