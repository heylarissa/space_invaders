#ifndef __SHOTS__
#define __SHOTS__

#include "enemies.h"
#include "player.h"
#include "obstacles.h"

#define ENEMY_SHOT_SPEED 10
#define SHOT_WIDTH 10
#define SHOT_HEIGHT 20
#define SHOT_STATE_ONE 0
#define SHOT_STATE_TWO 1


int enemy_active_shots(ENEMY (*enemies)[ENEMIES_PER_LINE], int *active_shots);
bool shot_in_this_column(SHOT *shots, int x);
void delete_shot(int position, SHOT **head);
void create_player_shot(PLAYER *p);
void update_player_shots(PLAYER *p, ENEMY (*enemies)[ENEMIES_PER_LINE], OBSTACLE obstacles[NUM_OBSTACLES], ENEMY *spaceship);
void draw_player_shots(SHOT *shots);
void update_enemies_shots(ENEMY (*enemies)[ENEMIES_PER_LINE], PLAYER *player, OBSTACLE obstacles[NUM_OBSTACLES]);
int kill_enemy(ENEMY enemies[NUM_ENEMIES_LINES][ENEMIES_PER_LINE], SHOT *shot, PLAYER *player);
bool player_collision(PLAYER player, ENEMY enemy);
bool red_spaceship_collision(ENEMY *spaceship, SHOT aux, PLAYER *player);
#endif