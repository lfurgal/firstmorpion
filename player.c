#include <stdlib.h>
#include "player.h"

struct player_t {
    int posTab[MAX_L][MAX_C];
    enum typePlayer_t Choix;
};

enum typePlayer_t switchPlayer(enum typePlayer_t p){
    return 1-p;
}

enum typePlayer_t getChoixPlayer(struct player_t *p){
    return p->Choix;
} 
void setPosPlayer(struct player_t *p, int l, int c){
    p->posTab[l][c]=1;
}

enum typePlayer_t getPlayerType(struct player_t *p){
    return p->Choix;
}

struct player_t * choixPlayer(struct player_t * p1, struct player_t * p2, enum typePlayer_t p){
    return (p==p1->Choix) ? p1 : p2;
}

struct player_t * initPlayer(enum typePlayer_t p){
    struct player_t *player = malloc(sizeof(struct player_t));
    player->Choix=p;
    int i = 0;
    while (i<MAX_L){
        int j = 0;
        while (j<MAX_C){
            player->posTab[i][j]=0;
            ++j;
        }
        ++i;
    }
    return player;
}
int isPlayerWin(struct player_t *p1){
    int i = 0;
    while (i < MAX_L){
        // Vérification des lignes et des colonnes
        if ((p1->posTab[i][0] + p1->posTab[i][1] + p1->posTab[i][2]) == 3) return 0; // Gagné
        if ((p1->posTab[0][i] + p1->posTab[1][i] + p1->posTab[2][i]) == 3) return 0; // Gagné
        ++i;
    }
    // Vérification des deux diagonales exactes
    if ((p1->posTab[0][0] + p1->posTab[1][1] + p1->posTab[2][2]) == 3) return 0; // Diagonale principale
    if ((p1->posTab[0][2] + p1->posTab[1][1] + p1->posTab[2][0]) == 3) return 0; // Diagonale secondaire

    return 1; // Pas gagné
}
