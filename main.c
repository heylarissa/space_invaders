#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

#define FALSE 0

void must_init(int test, const char *description)
{
    if (test)
        return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

int main()
{
    int end_game = FALSE;
    al_init();
    al_install_keyboard();
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 30.0);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    must_init(queue, "queue");

    ALLEGRO_DISPLAY *disp = al_create_display(320, 200);
    must_init(disp, "display");

    ALLEGRO_FONT *font = al_create_builtin_font();
    must_init(font, "font");

    /* registra os eventos na fila */
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    al_start_timer(timer);

    bool redraw = true;
    ALLEGRO_EVENT event;

    while (!end_game)
    {
        al_wait_for_event(queue, &event);
        if (redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, "Hello world!");
            al_flip_display();

            redraw = false;
        }
        else if ((event.type == ALLEGRO_EVENT_KEY_DOWN) || (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE))
            break;
        // atualiza tela
    }

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}