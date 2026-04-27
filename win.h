#ifndef WIN_H
#define WIN_H

#include "board.h"

#define MAX_NAME 32

// retourne : 0      (personne à gagné)
//          : 1,2,3 (joueur gagnant) 
//          : 4     (egalité)
int win_check_status(const Board *b, int nb_players);


 //  affiche le résultat final
void win_display_result(int status, const char player_names[][MAX_NAME]);


#endif
