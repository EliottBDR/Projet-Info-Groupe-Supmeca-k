#ifndef GRAVITY_H
#define GRAVITY_H


#include "board.h"


// applique la gravité sur une seule colonne.
void gravity_apply_col(Board *b, int col);


// applique la gravité sur tout le plateau
void gravity_apply_board(Board *b);


// retourne 1 si la case tout en haut de la colonne col est occupée

int gravity_col_is_full(const Board *b, int col);


// Retourne la ligne où la pièce doit se posée, ou -1 si impossible
int gravity_find_landing_row(const Board *b, int col);

#endif
