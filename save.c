#include "save.h" 
#include <stdio.h>
#include <stdlib.h>

/*Sauvegarde l’état actuel du jeu dans un fichier avec les étapes suivantes
 * Étapes :
 *   1) On ouvre le fichier en mode écriture binaire
 *   2) On écrit toute la structure GameState dedans
 *   3) On ferme le fichier
 * Si le fichier ne peut pas être ouvert : retourne -1
 * Sinon : retourne 0
 */



int save_game(GameState *gs){
    // Ouverture du fichier de sauvegarde
    FILE *f = fopen(SAVE_FILE, "wb");
    // SECURITE !! au cas ou fopen échoue
    if (f == NULL){
        return -1;
    }
    //on ecrit toute la structure GameState dans le fichier binaire pour sauvegarder
    fwrite(gs, sizeof(GameState),1,f);
    fclose(f);
    printf("partie sauvegardee \n");
    return 0;
}

/*Recharge une partie sauvegardée depuis le fichier
 * Étapes :
 *   1) On ouvre le fichier en lecture binaire
 *   2) On lit les données sauvegardées.
 *   3) On remet ces données dans GameState
 *   4) On ferme le fichier
 * Si aucune sauvegarde n’existe : retourne -1
 * Sinon : retourne 0
 */





int load_game (GameState *gs){
   //on rouvre le fichier en lecture seul 
    FILE* f = fopen(SAVE_FILE, "rb");
   //SECURITE
    if(f == NULL){
        return -1;
    }
    // on recupère la structure GameState écrit en binaire dans le fichier pour la mettre dans gs
    fread(gs, sizeof(GameState),1,f);
    fclose(f);
    printf("Partie chargee \n");
    return 0;
}
