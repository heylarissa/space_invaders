#ifndef __SHOTS__
#define __SHOTS__

#include "enemies.h"
#include "player.h"
#include "game.h"

int enemy_active_shots(ENEMY (*enemies)[ENEMIES_PER_LINE], int *active_shots);
bool shot_in_this_column(SHOT *shots, PLAYER p);
void delete_shot(int position, SHOT **head);
void create_player_shot(PLAYER *p);
void update_player_shots(PLAYER *p, ENEMY (*enemies)[ENEMIES_PER_LINE]);
void draw_player_shots(SHOT *shots);
void update_enemies_shots(ENEMY (*enemies)[ENEMIES_PER_LINE], PLAYER *player);
int kill_enemy(ENEMY enemies[NUM_ENEMIES_LINES][ENEMIES_PER_LINE], SHOT *shot);
bool player_collision(PLAYER player, ENEMY enemy);
#endif