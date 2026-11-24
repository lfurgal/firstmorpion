#ifndef SOLVER_H
#define SOLVER_H

//include
#include "player.h"
#include "move.h"
#include "show.h"


struct coup_t {
    int x;
    int y;
};
int isGrillePleine(struct morpion_t *game);
int minimax(struct morpion_t *game, int depth, int p);
char gagnantMorpion(struct morpion_t *game);
struct coup_t meilleurCoup(struct morpion_t *game, struct player_t *p);

#endif //SOLVER_H