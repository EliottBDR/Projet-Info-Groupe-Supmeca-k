#ifndef PLAYER_H  
#define PLAYER_H

#include "board.h"

#define MAX_NAME 32

// Structure d'un joueur :
typedef struct{
    int  id;                 // 1, 2 ou 3 
    char name[MAX_NAME];
}Player;

// Structure de l'état global de la partie : (C'est cette structure qui est sauvegardée/restaurée.)
typedef struct{
    Board board;
    Player players[MAX_PLAYERS];
    int nb_players;
    int current_idx;    // index dans players[] du joueur actif 
    int zone_size;      // taille de zone tirée pour ce tour 
    int turn;           // numéro du tour 
}GameState;

// Initialise les joueurs (saisie des noms ou noms par défaut) :
void player_init_all(GameState *gs, int nb_players);

// Retourne le joueur courant :
Player *player_current(GameState *gs);

// Passe au joueur suivant et tire la nouvelle taille de zone :
void player_next_turn(GameState *gs);

// Affiche l'en-tête du tour (nom du joueur, taille de zone) :
void player_display_turn_header(const GameState *gs);

#endif 
