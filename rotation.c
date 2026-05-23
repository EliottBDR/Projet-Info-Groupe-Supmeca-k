#include "rotation.h"
#include "board.h"
#include <stdlib.h>


/*
 * Calcule le coin supérieur gauche de la zone à faire tourner.
 * Le pivot représente le centre de la rotation.
 * À partir de ce centre, on remonte et on décale vers la gauche
 * pour retrouver le début de la zone, qui est indispensable pour les calculs qui vont suivre.
 */


void rotation_get_topleft(int pivot_row, int pivot_col, int zone_size, int *top_row, int *left_col) {
    int half = zone_size / 2;
    *top_row = pivot_row - half;
    *left_col = pivot_col - half;
}

/*
 * Vérifie si une rotation est autorisée.
 * Deux conditions doivent être respectées :
 * 1) La zone de rotation doit rester entièrement
 *    à l’intérieur du plateau.
 * 2) La pièce concernée doit bien se trouver
 *    dans cette zone.
 * Si tout est correct elle retourne 1.
 * Sinon elle retourne 0.
 */


int rotation_is_valid_pivot(int pivot_row, int pivot_col, int zone_size, int piece_row, int piece_col) {
    int top_row, left_col;
    rotation_get_topleft(pivot_row, pivot_col, zone_size, &top_row, &left_col); 

    // Vérifie si la zone sort du plateau
    if (top_row < 0 || top_row + zone_size > ROWS) {
    return 0;
  }
    if (left_col < 0 || left_col + zone_size > COLS) { 
    return 0;
  }
    // Vérifie si la pièce posée est bien dans la zone
    if (piece_row < top_row || piece_row >= top_row + zone_size) {
    return 0;
  }
    if (piece_col < left_col || piece_col >= left_col + zone_size) {
    return 0;
  }

    return 1;
}

/* Cette fonction fait tourner une zone du plateau autour d’un pivot.
 *en deux Étapes :
 * 1) On récupère la zone concernée.
 * 2) On la copie dans un tableau temporaire.
 * (important pour éviter d’écraser les données)
 * 3) On réécrit les cases dans leur nouvelle position après rotation.
 */

void rotation_rotate_zone(Board *b, int pivot_row, int pivot_col, int zone_size, int direction) {
    int r, c;
    int top_row, left_col;
    rotation_get_topleft(pivot_row, pivot_col, zone_size, &top_row, &left_col);

    /* Tableau temporaire :
     * on sauvegarde la zone avant de la modifier.
     * Taille maximale possible : 5x5.
     */
    
    int tmp[5][5]; // On suppose que zone_size max est 5
    for (r = 0; r < zone_size; r++) {
        for (c = 0; c < zone_size; c++) {
            tmp[r][c] = b->cells[top_row + r][left_col + c];
        }
    }

    
    // Rotation dans le sens horaire. Les lignes deviennent des colonnes.
    
    int n = zone_size;
    if (direction == ROT_CLOCKWISE) {
        for (r = 0; r < n; r++) {
            for (c = 0; c < n; c++) {
                b->cells[top_row + c][left_col + n - 1 - r] = tmp[r][c];
            }
        }
    }
         // Rotation dans le sens anti-horaire.
        
    else if (direction == ROT_COUNTERCLOCKWISE) {
        for (r = 0; r < n; r++) {
            for (c = 0; c < n; c++) {
                b->cells[top_row + n - 1 - c][left_col + r] = tmp[r][c];
            }
        }
    }
}

/*
 * Choisit aléatoirement une taille de zone.
 * La rotation pourra se faire :
 *   1) soit sur une zone 3x3
 *   2) soit sur une zone 5x5
 */


int rotation_random_size(){
    int a, b;
    b = rand()%100;
    if (b%2 == 0){
      a = 3;
    }
    if (b%2 == 1){
      a = 5;
    }
  return a;
}

















