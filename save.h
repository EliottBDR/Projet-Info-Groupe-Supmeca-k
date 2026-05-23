#ifndef SAVE_H 
#define SAVE_H
/*
 * Nom du fichier utilisé pour la sauvegarde.
 * Toutes les données du jeu seront écrites
 * dans ce fichier puis relues plus tard.
 */
#define SAVE_FILE "sauvegarde.bin"
#include "player.h"
int save_game(GameState *gs);
int load_game(GameState *gs);
#endif 
