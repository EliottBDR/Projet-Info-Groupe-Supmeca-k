#define _XOPEN_SOURCE 500 
#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "board.h"
#include "gravity.h"
#include "rotation.h"
#include "player.h"
#include "win.h"
#include "save.h"

#define ANIM_DELAY_MS 120

// verifie si toutes les colonnes sont pleines (match nul) 
static int is_board_full(const Board *b){
    for(int c = 0; c < COLS; c++){
        // on regarde uniquement la ligne du haut si elle est occupee partout, le plateau est plein
        if(b->cells[0][c] == EMPTY){
            return (0);
        }
    }
    return 1;
}

/*
   animate_drop : fait tomber une piece dans une colonne case par case
   on place la piece temporairement ligne par ligne et on efface entre chaque
*/
static void animate_drop(Board *b, int col, int target_row, int player_id){
    for(int r = 0; r <= target_row; r++){
        printf("\033[2J\033[H");
        b->cells[r][col] = player_id; // on pose la piece temporairement sur la ligne r
        board_display(b);
        usleep(ANIM_DELAY_MS * 1000); // on attend un peu avant la frame suivante
        b->cells[r][col] = EMPTY;
    }
}

/*
   animate_gravity : anime la chute des pieces apres une rotation

   before = plateau apres rotation (des pieces sont en l'air)
   after  = plateau apres gravite (positions finales)
 
   on regarde combien chaque piece doit descendre, et on affiche
   les etapes intermediaires pour que ca ressemble a une vraie chute
*/
static void animate_gravity(Board *before, const Board *after){
    int val;
    int fall;
    int target;
    int cur_r;
    Board frame;

    // ETAPE 1 : calculer combien de cases chaque piece doit tomber et garder le maximum
    //ce maximum nous donne le nombre de frames a afficher
    int max_fall = 0;

    for(int c = 0; c < COLS; c++){
        for(int r = 0; r < ROWS; r++){

            val = before->cells[r][c];

            // on ignore les cases vides et les blocs indestructibles 
            if(val == EMPTY || val == INDESTRUCTIBLE){
                continue;
            }

            // on cherche ou cette piece atterrit dans l'etat final 
            // on part du bas pour trouver la position la plus basse 
            for(int r2 = ROWS - 1; r2 >= r; r2--){
                if(after->cells[r2][c] == val){
                    fall = r2 - r;  // nombre de cases a descendre 
                    if(fall > max_fall){
                        max_fall = fall; // on garde la chute la plus longue
                    }
                    break;
                    
                }
            }
        }
    }

    // si aucune piece ne bouge pas besoin d'animer 
    if(max_fall == 0){
        return;
    }

    // ETAPE 2 : afficher les frames une par une
   // a chaque frame chaque piece avance d'un cran vers sa destination
    
    for(int step = 1; step <= max_fall; step++){

        // on repart de l'etat "before" a chaque frame 
        memcpy(&frame, before, sizeof(Board));

        // on repositionne chaque piece selon l'avancement (step) 
        for(int c = 0; c < COLS; c++){
            for(int r = ROWS - 1; r >= 0; r--){

                val = before->cells[r][c];

                if(val == EMPTY || val == INDESTRUCTIBLE){
                    continue;
                }

                // retrouver la ligne d'arrivee de cette piece 
                target = r;
                for(int r2 = ROWS - 1; r2 >= r; r2--){
                    if(after->cells[r2][c] == val){
                        target = r2;
                        break;
                    }
                }

                fall = target - r;

                // la piece est deja a sa place, rien a faire
                if(fall <= 0){
                    continue;
                }

                // position intermediaire : on avance de "step" cases
                // mais on ne depasse jamais la destination finale
                if(step < fall){
                    cur_r = r + step;
                }
                else{
                    cur_r = r + fall;
                }

                // effacer l'ancienne position et poser a la nouvelle
                frame.cells[r][c]= EMPTY;
                frame.cells[cur_r][c] = val;
            }
        }

        // afficher la frame et attendre avant la suivante
        printf("\033[2J\033[H");
        printf(BOLD "   Gravite apres rotation...\n" RESET);
        board_display(&frame);
        usleep(ANIM_DELAY_MS * 1000);
    }
}

// demande au joueur de choisir une colonne disponible 
static int ask_column(const GameState *gs){
    int col;
    while(1){
        printf(BOLD "   Colonne (1-%d) : " RESET, COLS);
        if(scanf("%d", &col) != 1){
            while(getchar() != '\n');
            col = 0; // Valeur par défaut en cas d'erreur de saisie
        } 
        
        else{
            while(getchar() != '\n');
        }
        col--; // Ajustement pour l'indice du tableau
        
        if(col < 0 || col >= COLS){
            printf("   Colonne invalide. Reessayez.\n");
            continue;
        }
        if(gravity_col_is_full(&gs->board, col)){
            printf("   Colonne pleine ou bloquee. Reessayez.\n");
            continue;
        }
        return col;
    }
}

// demande au joueur de choisir un pivot valide pour la rotation 
static void ask_pivot(const GameState *gs, int piece_row, int piece_col, int *out_row, int *out_col){
    int pr, pc;

    int half = gs->zone_size / 2;
    int zsize = gs->zone_size;

    printf("\n   Choisissez le pivot de la zone %dx%d\n", zsize, zsize);
    printf("   (Le pivot doit etre a au moins %d case(s) du bord\n", half);
    printf("    et la zone doit contenir la piece posee en ligne %d, col %d)\n",piece_row + 1, piece_col + 1);

    while(1){
        printf(BOLD "   Ligne pivot (1-%d) : " RESET, ROWS);
        if(scanf("%d", &pr) != 1){
            while (getchar() != '\n'); 
            pr = 0; 
        }
        else{
            while (getchar() != '\n'); 
        }
        pr--;

        printf(BOLD "   Colonne pivot (1-%d) : " RESET, COLS);
        if(scanf("%d", &pc) != 1){
            while (getchar() != '\n'); 
            pc = 0; 
        } 
        else{
            while (getchar() != '\n'); 
        }
        pc--;

        if(pr < 0 || pr >= ROWS || pc < 0 || pc >= COLS){
            printf("   Coordonnees hors plateau. Reessayez.\n");
            continue;
        }
        if(!rotation_is_valid_pivot(pr, pc, zsize, piece_row, piece_col)){
            printf("   Pivot invalide : zone hors plateau ou ne contient pas la piece.\n");
            continue;
        }
        *out_row = pr;
        *out_col = pc;
        printf("\033[2J\033[H");
        printf(BOLD "   Zone selectionnee (en vert) :\n" RESET);
        board_display_highlight(&gs->board, pr, pc, zsize);
        return;
    }
}

// demande H pour horaire ou A pour anti-horaire 
static int ask_direction(void){
    char c ;
    while(1){
        printf(BOLD "   Sens de rotation - Horaire = H / Anti-horaire = A : " RESET);
        scanf(" %c", &c);
        while(getchar() != '\n');

        if(c == 'H' || c == 'h'){
            return ROT_CLOCKWISE;
        }
        if(c == 'A' || c == 'a'){
            return ROT_COUNTERCLOCKWISE;
        }
        printf("   Saisie invalide. Entrez H ou A.\n");
    }
}

// propose de sauvegarder apres chaque tour 
static void ask_save(GameState *gs){
    char c;
    int res;

    printf(BOLD "\n   Sauvegarder la partie ? (Oui/Non) : " RESET);
    fflush(stdout);
    scanf(" %c", &c);
    while(getchar() != '\n');

    if(c == 'O' || c == 'o'){
        res = save_game(gs);
        if(res != 0){
            printf("   Erreur lors de la sauvegarde.\n");
        }
        fflush(stdout);
        usleep(800 * 1000);
    }
}

// affiche le menu principal du jeu et récupère le choix du joueur
static int menu_main(void){
    FILE *f;
    int choix;
    // Efface l'écran (\033[2J) et replace le curseur tout en haut à gauche (\033[H)
    printf("\033[2J\033[H");
    printf(BOLD YELLOW
           "   |==================================|\n"
           "   |            PUISSANCE 5           |\n"
           "   |==================================|\n"
           "   |  1. Nouvelle partie              |\n");
    //Si un fichier de sauvegarde existe l'option "Reprendre la sauvegarde" apparaît 
    f = fopen("sauvegarde.bin", "rb"); 
    if(f != NULL) {
        printf("   |  2. Reprendre la sauvegarde      |\n");
        //on referme le fichier pour libérer les ressources système
        fclose(f);
    }
    printf(
           "   |  0. Quitter                      |\n"
           "   |==================================|\n" RESET);
    printf(BOLD "   Choix : " RESET);
    
    if(scanf("%d", &choix) != 1){
        while (getchar() != '\n');
        choix = 0;
    } 
    else{
        while (getchar() != '\n');
    }
    return choix;
}

// demande le nombre de joueurs (2 ou 3) 
static int menu_nb_players(void){
    int n;

    while(1){
        printf(BOLD "   Nombre de joueurs (2 ou 3) : " RESET);
        if(scanf("%d", &n) != 1){
            while(getchar() != '\n');
            n = 2;
        } 
        else {
            while(getchar() != '\n');
        }

        if(n == 2 || n == 3){
            return n;
        }
        printf("   Valeur invalide. Entrez 2 ou 3.\n");
    }
}

// boucle principale du jeu qui tourne jusqu'a ce qu'un joueur gagne ou que le plateau soit plein
static void game_loop(GameState *gs){
    int col;
    int piece_row, pivot_row, pivot_col;
    int direction;
    int status;
    Board after;
    char names[MAX_PLAYERS][MAX_NAME];
    Player *p;

    while(1){
        //on récupère le joueur actif
        p = player_current(gs);

        //affichage du debut de tour 
        printf("\033[2J\033[H");
        player_display_turn_header(gs);
        board_display(&gs->board); //On affiche le bandeau du tour et le plateau actuel

        // le joueur choisit une colonne et on fait tomber la piece 
        col = ask_column(gs);
        piece_row = gravity_find_landing_row(&gs->board, col);
        if (piece_row == -1) {
            printf("   Erreur : colonne pleine !\n");
            continue;
        }
        //On lance l'animation de descente de la pièce case par case
        animate_drop(&gs->board, col, piece_row, p->id);
        
        //on l'inscrit définitivement dans la matrice du plateau de jeu
        gs->board.cells[piece_row][col] = p->id;

        // le joueur choisit le pivot et le sens de rotation 
        ask_pivot(gs, piece_row, col, &pivot_row, &pivot_col);
        direction = ask_direction();

        //on applique la rotation 
        rotation_rotate_zone(&gs->board, pivot_row, pivot_col, gs->zone_size, direction);

        // on calcule l'etat apres gravite sur une copie puis on anime la chute et on applique le resultat
       
        memcpy(&after, &gs->board, sizeof(Board));  //on fait une copie du plateau actuel dans 'after'
        gravity_apply_board(&after);                //on applique la gravité définitive sur cette copie 'after'
        animate_gravity(&gs->board, &after);        //on compare l'ancien état (&gs->board) et le nouveau (&after) pour afficher l'animation de chute
        memcpy(&gs->board, &after, sizeof(Board));  //on applique définitivement le résultat physique sur le vrai plateau du jeu

        // affichage du resultat du tour 
        printf("\033[2J\033[H");
        printf(BOLD "   Resultat du tour :\n" RESET);
        board_display(&gs->board);
        usleep(500 * 1000);

        // on verifie si quelqu'un a gagne ou si le plateau est plein
        status = win_check_status(&gs->board, gs->nb_players);
        if(status != 0 || is_board_full(&gs->board)){
            for(int k = 0; k < gs->nb_players; k++){
                //Si la partie est finie, on copie les noms des joueurs dans un tableau local de sécurité avant d'appeler l'écran de résultats
                strncpy(names[k], gs->players[k].name, MAX_NAME - 1);
            }
            win_display_result(status, (const char (*)[MAX_NAME])names);
            return;
        }

        // tour suivant et option de sauvegarde 
        player_next_turn(gs);
        ask_save(gs);
    }
}

int main(void){
    GameState gs;
    int choice;
    int nb;

    srand((unsigned int)time(NULL));

    while(1){
        choice = menu_main();

        if(choice == 0){
            printf("   Au revoir !\n");
            break;
        }
        else if(choice == 2){
            if(load_game(&gs) != 0){
                printf("   Impossible de charger la sauvegarde.\n");
                continue;
            }
        }
        else if(choice == 1){
            nb = menu_nb_players();
            printf("\033[2J\033[H");
            printf(BOLD "   === Saisie des joueurs ===\n" RESET);
            player_init_all(&gs, nb);
        }
        else{
            printf("   Choix invalide.\n");
            continue;
        }

        game_loop(&gs);

        printf(BOLD "\n   Appuyez sur Entree pour revenir au menu...\n" RESET);
        while(getchar() != '\n'); // Attend un appui sur Entrée propre
    }

    return 0;
}
