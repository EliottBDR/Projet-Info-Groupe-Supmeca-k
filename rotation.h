#ifndef ROTATION_H 
#define ROTATION_H

#include "board.h"



/* Sens possibles de la rotation.
 * ROT_CLOCKWISE :
 * rotation vers la droite
 * (sens des aiguilles d’une montre)
 * ROT_COUNTERCLOCKWISE :
 * rotation vers la gauche
 * (sens inverse des aiguilles d’une montre)
 */


/* Sens de rotation */
#define ROT_CLOCKWISE        0   /* sens horaire     (droite) */
#define ROT_COUNTERCLOCKWISE 1   /* sens anti-horaire (gauche) */




/*Fait tourner une zone du plateau.
 * Paramètres :
 *- b : plateau du jeu
 *- pivot_row / pivot_col :
 *         centre de la rotation
 * - zone_size :
 *         taille de la zone à tourner
 *         (ex : 3 ou 5)
 * - direction :
 *         sens de rotation
 */
void rotation_rotate_zone(Board *b, int pivot_row, int pivot_col,
                           int zone_size, int direction);
/* Vérifie si une rotation est autorisée.
 * La fonction contrôle :
 *   - que la zone reste dans le plateau
 *   - que la pièce concernée se trouve bien
 *     dans cette zone
 * Retour :
 *   1 -> rotation valide
 *   0 -> rotation impossible
 */

int rotation_is_valid_pivot(int pivot_row, int pivot_col, int zone_size,
                             int piece_row, int piece_col);

/* Calcule le coin supérieur gauche indispensable
 * d’une zone de rotation.
 * À partir du pivot central, on retrouve le point de départ
 * de la sous-zone carrée.
 */

void rotation_get_topleft(int pivot_row, int pivot_col, int zone_size,
                           int *top_row, int *left_col);


/* Choisit aléatoirement une taille de zone.
 * La fonction retourne :
 *   - soit 3
 *   - soit 5
 */

int rotation_random_size(void);

#endif 
