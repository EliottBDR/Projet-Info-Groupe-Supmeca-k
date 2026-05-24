#ifndef BOARD_H
#define BOARD_H 

// Dimensions du plateau :
#define COLS 8
#define ROWS 6

// Valeurs des cases  :
#define EMPTY           0
#define PLAYER1         1
#define PLAYER2         2
#define PLAYER3         3
#define INDESTRUCTIBLE  4         

// Nombre de pièces à aligner pour gagner :
#define WIN_LEN 5                          

// Nombre max de joueurs :
#define MAX_PLAYERS 3                      

// Codes couleur ANSI :
#define RESET       "\033[0m"             
#define BOLD        "\033[1m"             
#define RED         "\033[1;31m"         
#define YELLOW      "\033[1;33m"          
#define CYAN        "\033[1;36m"          
#define MAGENTA     "\033[1;35m"  
#define WHITE       "\033[1;37m"           
#define BG_DARK     "\033[48;5;236m"       
#define BG_CORNER   "\033[48;5;88m"        


/*  Structure représentant le plateau de jeu :
      cells[row][col] : 
        0 = vide | 1,2,3 = pièce joueur | 4 = indestructible
      row 0 = ligne du haut, row ROWS-1 = ligne du bas.      */

typedef struct {                                            
    int cells[ROWS][COLS];                                
} Board;                                                 

// Initialise le plateau (tout vide + 4 coins indestructibles) :
void board_init(Board *b);

// Affiche le plateau avec couleurs ANSI :
void board_display(const Board *b);

// Affiche le plateau avec une zone surlignée (pivot_row/col, zone_size) :
void board_display_highlight(const Board *b, int pivot_row, int pivot_col, int zone_size);

// Affiche les numéros de colonnes au-dessus du plateau :
void board_display_col_numbers(void);

#endif                                    
