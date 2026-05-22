#include "gravity.h" 

 void gravity_apply_col(Board *b, int col) {
    int write_row = ROWS - 1;//write est la ou la pièce doit tomber

    //On parcourt la colonne de bas en haut
    for (int r = ROWS - 1; r >= 0; r--) {

        // Les indestructibles restent à leur place
        if (b->cells[r][col] == INDESTRUCTIBLE) {
            write_row = r - 1;
        }

        //Une pièce normale tombe
        else if (b->cells[r][col] != EMPTY) {
            //copier la pièce
            int piece = b->cells[r][col];

            // Vider l'ancienne case
            b->cells[r][col] = EMPTY;

            // Poser la pièce plus bas
            b->cells[write_row][col] = piece;

            write_row--;
        }
    }
}

 //gravité sur toutes les colonnes

void gravity_apply_board(Board *b) {
    for (int c=0; c < COLS; c++){
        gravity_apply_col(b, c);
    }
}



 //teste si une colonne est pleine en retournant 1 si plein ou 0 si case du haut vide
int gravity_col_is_full(const Board *b, int col) {
    return (b->cells[0][col] != EMPTY);
}

int gravity_find_landing_row(const Board *b, int col) {
    //Vérifier si l'entrée est bloquée
    if (b->cells[0][col] != EMPTY){
     return -1;
    }
    int landing_row = 0;
    // on descend tant que c'est vide et si un obstacle rencontré on renvoie la valeur 
    for (int r = 0; r < ROWS; r++) {
        if (b->cells[r][col] == EMPTY) {
            landing_row = r;
        } else {
            break; // Obstacle trouvé
        }
    }
    return landing_row; // On retourne juste l'indice
}
