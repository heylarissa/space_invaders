#ifndef __DISPLAY__
#define __DISPLAY__

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#define GREEN al_map_rgb(52, 255, 0)
#define WHITE al_map_rgb(255, 255, 255)
#define RED al_map_rgb(255, 0, 0)
#define BLACK al_map_rgb(0, 0, 0)

#define HEIGHT_DISPLAY 800
#define WIDTH_DISPLAY 1600
#define MARGIN 100
#define TOTAL_WIDTH WIDTH_DISPLAY + MARGIN
#define TOTAL_HEIGHT HEIGHT_DISPLAY + MARGIN

#define KEY_SEEN 1
#define KEY_RELEASED 2

typedef struct
{
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_TIMER *timer;
    ALLEGRO_DISPLAY *display;
    ALLEGRO_FONT *font;
} WINDOW;


void must_init(bool test, const char *description);

#endif