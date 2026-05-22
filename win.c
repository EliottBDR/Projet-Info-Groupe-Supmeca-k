#include "win.h" 
#include <stdio.h>
 
int win_check_status(const Board *b, int nb_players) {
    int r, c,i;
    int gagnants[3] = {0, 0, 0};//tableau des gagnants 
    
    for (r = 0; r < ROWS; r++) {
        for (c= 0; c < COLS; c++) {
            int p = b->cells[r][c]; //p prends la valeur de la case actuel
            
            
            if (p <= 0||p == INDESTRUCTIBLE) { 
                continue;  //on passe à la prochaine case car la case n'est pas une piece
            }
            
            //horizontal
            if (c+4 < COLS && b->cells[r][c+1] == p && b->cells[r][c+2] == p && b->cells[r][c+3] == p &&  b->cells[r][c+4] == p) {
                gagnants[p-1] = 1;
            }
            
            //vertival
            if (r + 4 < ROWS &&  b->cells[r+1][c] == p && b->cells[r+2][c] == p && b->cells[r+3][c] == p &&  b->cells[r+4][c] == p) {
                gagnants[p-1] = 1;    
            }
            
            //diagonal vers le haut a droite
            if (r - 4 >= 0 && c+4 < COLS &&  b->cells[r-1][c+1] == p && b->cells[r-2][c+2] == p && b->cells[r-3][c+3] == p && b->cells[r-4][c+4] == p) {
                gagnants[p-1] = 1;    
            }
              
            //diagonal vers le bas a droite
            if (r + 4 < ROWS && c + 4 < COLS && b->cells[r+1][c+1]== p &&  b->cells[r+2][c+2] == p && b->cells[r+3][c+3] == p &&b->cells[r+4][c+4] == p ) {
                gagnants[p-1] = 1; 
            }
        }
    }
    
   //compte le nombres de gagnants et "winner" prend la valeur du dernier gagnant 
    int total_winners = 0;
    int winner = 0;
    for (i = 0; i < nb_players; i++) {
        if (gagnants[i] == 1) {
            total_winners++;
            winner = i + 1;
        }
    }
    
    if (total_winners > 1) {
        return 4;  //plusieurs joueurs ont gagné
    }
    if (total_winners == 1) {
        return winner;  // Retourne l'ID du gagnant 
    }
    return 0;  // personne n'a gagné 
}

//affiche le résultat final 
void win_display_result(int status, const char player_names[][MAX_NAME]) {
    printf("\n==============================\n");
    
    if (status == 4) {
        printf("   EGALITE ENTRE PLUSIEURS JOUEURS ! \n");
    } 
    else if (status >= 1 && status <= 3) {
        printf("  BRAVO ! VICTOIRE DE : %s \n", player_names[status - 1]);
    } 
    else {
        printf("       MATCH NUL ! (Plateau plein)    \n");
    }
    
    printf("==============================\n");
}
