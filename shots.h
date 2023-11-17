#ifndef __SHOTS__
#define __SHOTS__

#include "player.h"
#include "game.h"
#include "enemies.h"
#include "shots.h"

bool shot_in_this_column(SHOT *shots, PLAYER p);
void delete_shot(int position, SHOT **head);
void create_player_shot(PLAYER *p);
void update_player_shots(PLAYER *p);
void draw_player_shots(SHOT *shots);

#endif