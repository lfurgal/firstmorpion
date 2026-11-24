#ifndef MOVE_H
#define MOVE_H

//include
#include "show.h"
#include "player.h"
//Macros
#define MAX_TOURS 9

void movePlateau(struct player_t *p, struct morpion_t *jeu, int l, int c);
//modif plateau courant et celui du player + verif si move est possible 
int movOK(struct morpion_t *jeu, int l, int c);
char siglePlayer(struct player_t* p);
#endif //MOVE_H