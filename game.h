#ifndef _GAME_
#define _GAME_

#include "display.h"
#include "enemies.h"
#include "shots.h"
#include "player.h"

void start_new_round(ENEMY (*enemies)[ENEMIES_PER_LINE], ENEMY *spaceship, SPRITES *sprites, PLAYER *player, OBSTACLE obstacles[NUM_OBSTACLES]);
void destroy_game(ENEMY (*enemies)[ENEMIES_PER_LINE], PLAYER *player,
                  SPRITES *sprites, ALLEGRO_FONT *font, ALLEGRO_TIMER *timer,
                  ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_DISPLAY *disp);
void init_game(PLAYER *player, ENEMY (*enemies)[ENEMIES_PER_LINE], ENEMY *spaceship, SPRITES *sprites, OBSTACLE obstacles[NUM_OBSTACLES]);
void draw_game(OBSTACLE obstacles[NUM_OBSTACLES], SPRITES *sprites, ALLEGRO_FONT *font, PLAYER *player, int currentRound, ENEMY (*enemies)[ENEMIES_PER_LINE], ENEMY spaceship);
void game_logic(unsigned char key[], PLAYER *player, GameState *gameState, int *frame_count, SPRITES *sprites, ENEMY *spaceship, ENEMY (*enemies)[ENEMIES_PER_LINE], OBSTACLE obstacles[NUM_OBSTACLES]);
void redraw_screem(GameState *gameState, SPRITES *sprites, ALLEGRO_FONT *font, int currentRound, OBSTACLE obstacles[NUM_OBSTACLES], PLAYER *player, ENEMY (*enemies)[ENEMIES_PER_LINE], ENEMY spaceship);
void game_pause(ALLEGRO_TIMER *timer, GameState *gameState);

#endif