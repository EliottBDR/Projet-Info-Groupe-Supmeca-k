#ifndef ROTATION_H 
#define ROTATION_H

#include "board.h"

/* Sens de rotation */
#define ROT_CLOCKWISE        0   /* sens horaire     (droite) */
#define ROT_COUNTERCLOCKWISE 1   /* sens anti-horaire (gauche) */

void rotation_rotate_zone(Board *b, int pivot_row, int pivot_col,
                           int zone_size, int direction);

int rotation_is_valid_pivot(int pivot_row, int pivot_col, int zone_size,
                             int piece_row, int piece_col);

void rotation_get_topleft(int pivot_row, int pivot_col, int zone_size,
                           int *top_row, int *left_col);

int rotation_random_size(void);

#endif 
