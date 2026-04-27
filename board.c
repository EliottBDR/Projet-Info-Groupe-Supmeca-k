#include "board.h"
#include <stdio.h>
#include <string.h>

// Code couleur pour la zone de rotation en surbrillance (fond vert)
#define BG_GREEN "\033[42m"

// Symboles des joueurs associés aux valeurs
static const char *SYMBOLS[] = { " ", ">", "(", "[", "#" };

// Couleurs de texte associées aux valeurs (Assurez-vous que ces macros sont dans board.h)
static const char *COLORS[]  = { RESET, YELLOW, CYAN, MAGENTA, RED };

// board_init : initialise toutes les cases à EMPTY, puis place les cases indestructibles aux 4 coins 
void board_init(Board *b) {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            b->cells[r][c] = EMPTY;
        }
    }

    // Placement des 4 coins indestructibles
    b->cells[0][0] = INDESTRUCTIBLE;
    b->cells[0][COLS - 1] = INDESTRUCTIBLE;
    b->cells[ROWS - 1][0] = INDESTRUCTIBLE;
    b->cells[ROWS - 1][COLS - 1] = INDESTRUCTIBLE;
}

// board_display_col_numbers : affiche les indices de colonnes parfaitement centrés
void board_display_col_numbers(void){
    printf("   "); // Marge pour s'aligner sur la bordure gauche "  |"
    for (int i = 0; i < COLS; i++){
        // On utilise 4 caractères de large pour correspondre à "---+"
        printf(" %d  ", i + 1); 
    }
    printf("\n");
}

// board_display_line_separator : dessine une ligne horizontale de bordure (+---+---+) 
static void board_display_line_separator(void){
    printf("  +");
    for (int i = 0; i < COLS; i++){
        printf("---+");
    }
    printf("\n");
}

// board_display_generic : fonction interne unique pour l'affichage complet
static void board_display_generic(const Board *b, int highlight, int pivot_row, int pivot_col, int zone_size){
    int half = zone_size / 2;
    int top  = pivot_row - half;
    int left = pivot_col - half;

    board_display_col_numbers();
    board_display_line_separator();

    for (int r = 0; r < ROWS; r++){
        printf("  |"); // Début de la ligne de données
        for (int c = 0; c < COLS; c++){
            int val = b->cells[r][c];

            // Si le mode highlight est actif et que la case est dans la zone
            if (highlight && r >= top && r < top + zone_size && c >= left && c < left + zone_size){
                printf(BG_GREEN);
            }

            // Affichage de la case (3 caractères de contenu + le séparateur '|')
            printf(" %s%s %s|", COLORS[val], SYMBOLS[val], RESET);
        }
        
        // Affichage du numéro de ligne à droite après la dernière barre '|'
        printf(" %d\n", r + 1);
        
        board_display_line_separator();
    }
}

// board_display : affiche le plateau standard
void board_display(const Board *b){
    board_display_generic(b, 0, 0, 0, 0);
}

// board_display_highlight : affiche le plateau avec la zone de rotation en vert
void board_display_highlight(const Board *b, int pivot_row, int pivot_col, int zone_size){
    board_display_generic(b, 1, pivot_row, pivot_col, zone_size);
}
