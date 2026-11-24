#include "move.h"

//modif plateau courant et celui du player + verif si move est possible 
int movOK(struct morpion_t *jeu, int l, int c){
    return getCaseMorpion(jeu, l, c)==' ';
}

char siglePlayer(struct player_t* p){
    return (getChoixPlayer(p)==CROIX) ? 'X' : 'O';
}

void movePlateau(struct player_t *p, struct morpion_t *jeu, int l, int c){
    if (movOK(jeu, l, c)) {
        setCaseMorpion(jeu, l, c, siglePlayer(p));
        setPosPlayer(p, l, c);
    }
}
