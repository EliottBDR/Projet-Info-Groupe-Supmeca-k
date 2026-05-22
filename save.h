#ifndef SAVE_H 
#define SAVE_H
#define SAVE_FILE "sauvegarde.bin"
#include "player.h"
int save_game(GameState *gs);
int load_game(GameState *gs);
#endif 
