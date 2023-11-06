#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#define KEY_SEEN 1
#define KEY_RELEASED 2

#define TRUE 1
#define FALSE 0

#define LEFT 0
#define RIGHT 1

#define GREEN al_map_rgb(52, 255, 0)
#define WHITE al_map_rgb(255, 255, 255)
#define RED al_map_rgb(255, 0, 0)
#define BLACK al_map_rgb(0, 0, 0)

#define HEIGHT_DISPLAY 800
#define WIDTH_DISPLAY 1600
#define MARGIN 100
#define TOTAL_WIDTH WIDTH_DISPLAY + MARGIN
#define TOTAL_HEIGHT HEIGHT_DISPLAY + MARGIN

#define SIZE_PLAYER 50

typedef struct SPRITES_T
{
    ALLEGRO_BITMAP *_sheet;

    ALLEGRO_BITMAP *redship;
    ALLEGRO_BITMAP *aliens[6];
    ALLEGRO_BITMAP *player;
    ALLEGRO_BITMAP *shield[5];
    ALLEGRO_BITMAP *spaceinvaderslogo;
    ALLEGRO_BITMAP *explosion;
    ALLEGRO_BITMAP *shot;

} SPRITES;

typedef struct shot
{
    int direction;
    float x, y;
    struct shot *next;
} SHOT;

typedef struct player
{
    float x, y;
    int score;
    int lives;
    SHOT *shots; // lista de tiros ativos

} PLAYER;
// player sprite will require two costumes, a regular one and a dead one
// a sprite for the player, aliens, spaceship and bullets
typedef struct enemy // apenas 2 inimigos podem atirar
{
    float x, y;
    int size;
    int r, g, b; // cor do inimigo
    int type;    // existem 3 tipos de inimigos
    int alive;   // vivo?
    SHOT shot;   // tiro do inimigo - um por vez
    struct enemy *next;
} ENEMY;

void must_init(bool test, const char *description)
{
    if (test)
        return;

    printf("Couldn't initialize %s\n", description);
    exit(1);
}
// Seleciona a parte da imagem a ser cortada
ALLEGRO_BITMAP *select_sprite(ALLEGRO_BITMAP *img, int x, int y, int w, int h)
{
    ALLEGRO_BITMAP *sprite = al_create_sub_bitmap(img, x, y, w, h);
    must_init(sprite, "select sprite");
    return sprite;
}

void init_sprites(SPRITES *sprites)
{
    sprites->_sheet = al_load_bitmap("./assets/sprites.png");
    must_init(sprites->_sheet, "sprites");

    sprites->spaceinvaderslogo = select_sprite(sprites->_sheet, 160, 0, (410 - 160), 170);
}

int main()
{
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

    ALLEGRO_EVENT event;

    PLAYER player;
    player.x = WIDTH_DISPLAY / 2;
    player.y = HEIGHT_DISPLAY - SIZE_PLAYER;
    player.score = 0;

    ENEMY *enemy;
    enemy = malloc(sizeof(ENEMY));
    enemy->size = SIZE_PLAYER;
    enemy->next = NULL;
    enemy->x = MARGIN;
    enemy->y = 100 - SIZE_PLAYER;

    int menu = TRUE;
    int enemydirection = LEFT;

    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));
    SPRITES *sprites = malloc(sizeof(SPRITES));
    init_sprites(sprites);
    al_start_timer(timer);

    while (1)
    {
        al_wait_for_event(queue, &event);

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            if (key[ALLEGRO_KEY_ESCAPE])
                done = true;

            if (menu == TRUE)
            {
                if ((key[ALLEGRO_KEY_SPACE]) || (key[ALLEGRO_KEY_ENTER]))
                {
                    menu = FALSE;
                }
            }
            else
            {
                /* enemy logic */
                if (enemydirection == LEFT)
                {
                    enemy->x += 10;
                }
                else
                {
                    enemy->x -= 10;
                }

                if ((enemy->x == TOTAL_WIDTH - SIZE_PLAYER - MARGIN) || (enemy->x == MARGIN))
                {
                    enemy->y += SIZE_PLAYER / 2;
                    enemydirection = !enemydirection; // inverte a direção
                }

                /* player logic */
                if (key[ALLEGRO_KEY_LEFT] && (player.x != MARGIN))
                {
                    player.x -= SIZE_PLAYER / 2;
                }
                else if (key[ALLEGRO_KEY_RIGHT] && player.x != TOTAL_WIDTH - SIZE_PLAYER - MARGIN)
                {
                    player.x += SIZE_PLAYER / 2;
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
                al_draw_bitmap(sprites->spaceinvaderslogo, (TOTAL_WIDTH) / 2 - (410 - 160)/2 , (TOTAL_HEIGHT) / 2 - 2*MARGIN, 0);

                al_draw_textf(font, WHITE, (TOTAL_WIDTH) / 2, MARGIN, ALLEGRO_ALIGN_CENTER, "MENU");
                al_draw_textf(font, GREEN, (TOTAL_WIDTH) / 2, (TOTAL_HEIGHT) / 2, ALLEGRO_ALIGN_CENTER, "PRESS SPACE OR ENTER TO START");
            }
            else
            {
                // al_draw_textf(font, WHITE, 0, 50, 0, "X: %.1f Y: %.1f", player.x, player.y); //DEBUG
                al_draw_textf(font, WHITE, 0, 0, 0, "SCORE: %d", player.score);

                al_draw_filled_rectangle(enemy->x, enemy->y, enemy->x + SIZE_PLAYER, enemy->y + SIZE_PLAYER, RED);

                al_draw_filled_rectangle(player.x, player.y, player.x + SIZE_PLAYER, player.y + SIZE_PLAYER, WHITE);
            }
            al_flip_display();

            redraw = false;
        }
    }

    al_destroy_bitmap(sprites->_sheet);
    al_destroy_bitmap(sprites->spaceinvaderslogo);
    // al_destroy_bitmap(sprites->_sheet);
    // al_destroy_bitmap(sprites->_sheet);

    free(sprites);
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}