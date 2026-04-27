#include "save.h"
#include <stdio.h>
#include <stdlib.h>

int save_game(GameState *gs){
    FILE *f = fopen(SAVE_FILE, "wb");
    if (f == NULL){
        return -1;
    }
    fwrite(gs, sizeof(GameState),1,f);
    fclose(f);
    printf("partie sauvegardee \n");
    return 0;
}

int load_game (GameState *gs){
    FILE* f = fopen(SAVE_FILE, "rb");
    if(f == NULL){
        return -1;
    }
    fread(gs, sizeof(GameState),1,f);
    fclose(f);
    printf("Partie chargee \n");
    return 0;
}
