#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#include "display.h"
#include "game.h"
#include "player.h"
#include "enemies.h"
#include "shots.h"

void init_game(PLAYER *player, ENEMY **enemies, ENEMY *spaceship, SPRITES *sprites)
{
    init_sprites(sprites);
    init_player(player, sprites);
    init_spaceship(spaceship, sprites);
    *enemies = init_enemies();
}

void draw_player(PLAYER player, ALLEGRO_FONT *font, SPRITES *sprites)
{
    al_draw_bitmap(sprites->player, player.x, player.y, 0);
    draw_player_shots(player.shots, font);
}


int main()
{
    // TODO: Refatorar toda a inicialização do allegro para uma única struct
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 30.0);
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
    int menu = TRUE;

    ALLEGRO_EVENT event;
    SPRITES *sprites = (SPRITES *)malloc(sizeof(SPRITES));
    PLAYER player;
    ENEMY *spaceship = (ENEMY *)malloc(sizeof(ENEMY));
    ENEMY *enemies = NULL;

    init_game(&player, &enemies, spaceship, sprites);

    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));

    al_start_timer(timer);

    while (1)
    {
        al_wait_for_event(queue, &event);

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            if (key[ALLEGRO_KEY_ESCAPE])
                done = true;

            if ((menu == TRUE) && ((key[ALLEGRO_KEY_SPACE]) || (key[ALLEGRO_KEY_ENTER])))
            {
                menu = FALSE;
            }
            else
            {
                /* enemy logic */
                // update_enemies(enemies, spaceship);

                /* player logic */
                update_player_shots(&player);

                if (key[ALLEGRO_KEY_LEFT] && (player.x >= 0))
                {
                    player.x -= SIZE_PLAYER / 2;
                }
                else if (key[ALLEGRO_KEY_RIGHT] && player.x <= (TOTAL_WIDTH - player.w))
                {
                    player.x += SIZE_PLAYER / 2;
                }
                else if (key[ALLEGRO_KEY_SPACE])
                {
                    create_player_shot(&player);
                }
            }

            for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
                key[i] &= KEY_SEEN;

            redraw = true;
            break;

        case ALLEGRO_EVENT_KEY_DOWN:                               // tecla pressionada
            key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED; // armazena no vetor na posição respectiva ao keycode da tecla
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

            if (menu)
            {
                al_draw_bitmap(sprites->spaceinvaderslogo, (TOTAL_WIDTH) / 2 - (410 - 160) / 2, (TOTAL_HEIGHT) / 2 - 2 * MARGIN, 0);
                al_draw_textf(font, WHITE, (TOTAL_WIDTH) / 2, MARGIN, ALLEGRO_ALIGN_CENTER, "MENU");
                al_draw_textf(font, GREEN, (TOTAL_WIDTH) / 2, (TOTAL_HEIGHT) / 2, ALLEGRO_ALIGN_CENTER, "PRESS SPACE OR ENTER TO START");
            }
            else
            {
                // desenha tela
                al_draw_textf(font, WHITE, 0, 0, 0, "SCORE %f", player.x); // score do player
                draw_lives(player.lives, sprites->player, font);           // vidas do player

                // desenha inimigos
                al_draw_scaled_bitmap(sprites->spaceship, 0, 0,
                                      al_get_bitmap_width(sprites->spaceship),
                                      al_get_bitmap_height(sprites->spaceship),
                                      spaceship->x, spaceship->y,
                                      al_get_bitmap_width(sprites->spaceship) * 0.5,
                                      al_get_bitmap_height(sprites->spaceship) * 0.5, 0); // desenha nave vermelha

                draw_enemies(enemies, sprites);

                // desenha player
                al_draw_bitmap(sprites->player, player.x, player.y, 0);
                draw_player_shots(player.shots, font);

                // desenha tiros dos inimigos
                // se tiro atingiu player, imprime outra animação do player
                // se tiro atingiu inimigo, imprime inimigo explodindo
                // pros obstáculos usar uma imagem e só plotar o pixel quando o tiro atingir
                al_draw_line(0, TOTAL_HEIGHT - MARGIN / 2, TOTAL_WIDTH, TOTAL_HEIGHT - MARGIN / 2, GREEN, 5);
            }
            al_flip_display();

            redraw = false;
        }
    }

    al_destroy_bitmap(sprites->_sheet);
    al_destroy_bitmap(sprites->spaceinvaderslogo);
    al_destroy_bitmap(sprites->spaceship);

    free(sprites);
    free(spaceship);
    free(enemies);

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}