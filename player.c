#include "player.h" 
#include "rotation.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Symboles associés à chaque joueur (index = player id) :
static const char *SYMBOLS[] = { " ", ">", "(", "[" };

// Couleurs ANSI des joueurs :
static const char *COLORS[]  = { RESET, YELLOW, CYAN, MAGENTA };

/*
  player_init_all : initialise la GameState pour une nouvelle partie.
  Demande les noms des joueurs (ou utilise "Joueur N" par défaut). 
*/
void player_init_all(GameState *gs, int nb_players){    
    gs->nb_players = nb_players;
    gs->current_idx = 0;
    gs->turn = 1;

    board_init(&gs->board);

    for (int i = 0; i < nb_players; i++){
        gs->players[i].id = i + 1;
        
        printf(BOLD "  Nom du joueur %d [%s%s%s] (Entree = defaut) : " RESET, i + 1, COLORS[i + 1], SYMBOLS[i + 1], RESET);
        
        // fgets lit la ligne entrée par l'utilisateur directement dans la structure
        fgets(gs->players[i].name, MAX_NAME, stdin);

        // Si l'utilisateur appuie directement sur Entrée (saisie vide)
        if (gs->players[i].name[0] == '\n'){
            // Génère le nom par défaut "Joueur N"
            sprintf(gs->players[i].name, "Joueur %d", i + 1);
        } 
        
        else {
            // Supprime le '\n' final laissé par fgets en fin de chaîne
            int len = strlen(gs->players[i].name);
            if (len > 0 && gs->players[i].name[len - 1] == '\n'){
                gs->players[i].name[len - 1] = '\0';
            }
        }
    }

    // Première taille de zone pour le premier tour
    gs->zone_size = rotation_random_size();   
}

// player_current : retourne un pointeur sur le joueur actif 
Player *player_current(GameState *gs) {                        
    return &gs->players[gs->current_idx];
}

// player_next_turn : passe au joueur suivant (rotation circulaire) et tire une nouvelle taille de zone 
void player_next_turn(GameState *gs) {                             
    gs->current_idx = (gs->current_idx + 1) % gs->nb_players;
    gs->turn++;
    gs->zone_size = rotation_random_size();
}

// player_display_turn_header : affiche le bandeau du tour courant 
void player_display_turn_header(const GameState *gs) {           
    const Player *p = &gs->players[gs->current_idx];

    printf("\n");
    printf(BOLD "  ==================================\n" RESET);
    printf(BOLD "  Tour %-3d | %s%s %s%s" RESET "\n", gs->turn, COLORS[p->id], SYMBOLS[p->id], p->name, RESET);
    printf(BOLD "    Taille de zone de rotation : %d\n" RESET, gs->zone_size);
    printf(BOLD "  ==================================\n\n" RESET);
}
