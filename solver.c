#include "solver.h"

int isGrillePleine(struct morpion_t *game) {
    int i = 0;
    while (i < MAX_L) {
        int j = 0;
        while (j < MAX_C) {
            if (getCaseMorpion(game, i, j) == ' ') {
                return 0; // Il reste au moins une case vide
            }
            ++j;
        }
        ++i;
    }
    return 1; // La grille est entièrement remplie (égalité)
}

int minimax(struct morpion_t *game, int depth, int p){
    char w = gagnantMorpion(game);
    
    // 1. Conditions d'arrêt terminales
    if (w == 'X') return 10 - depth; // Plus le score est haut, plus X gagne vite
    if (w == 'O') return depth - 10; // Plus le score est bas, plus O gagne vite
    if (isGrillePleine(game)) return 0; // Égalité

    // 2. Boucle récursive (si la partie n'est pas finie)
    if (p == CROIX){
        int maxEval = -1000;
        for (int i = 0; i < MAX_L; i++){
            for (int j = 0; j < MAX_C; j++){
                if (movOK(game, i, j)){
                    setCaseMorpion(game, i, j, 'X');
                    int eval = minimax(game, depth + 1, ROND);
                    setCaseMorpion(game, i, j, ' ');
                    if (eval > maxEval) {
                        maxEval = eval;
                    }
                }
            }   
        }
        return maxEval;
    }
    else {
        int minEval = 1000;
        for (int i = 0; i < MAX_L; i++){
            for (int j = 0; j < MAX_C; j++){
                if (movOK(game, i, j)){
                    setCaseMorpion(game, i, j, 'O');
                    int eval = minimax(game, depth + 1, CROIX);
                    setCaseMorpion(game, i, j, ' ');
                    if (eval < minEval) {
                        minEval = eval;
                    }
                }
            }   
        }
        return minEval;
    }
}
char gagnantMorpion(struct morpion_t *game){
    for (int i = 0; i<MAX_L; i++){
        if ((getCaseMorpion(game, i, 1)==getCaseMorpion(game, i, 0))&&(getCaseMorpion(game, i, 0)==getCaseMorpion(game, i, 2)) && getCaseMorpion(game, i, 0)!=' '){
            return getCaseMorpion(game, i, 0);
        }
        if ((getCaseMorpion(game, 0, i)==getCaseMorpion(game, 1, i))&&(getCaseMorpion(game, 0, i)==getCaseMorpion(game, 2, i)) && getCaseMorpion(game, 0, i)!=' '){
            return getCaseMorpion(game, 0, i);
        }
        //diagonale
    }
    if (getCaseMorpion(game, 0, 2)==getCaseMorpion(game, 1, 1)&&getCaseMorpion(game, 0, 2)==getCaseMorpion(game, 2, 0)&&getCaseMorpion(game, 1, 1)!=' '){
        return getCaseMorpion(game, 1, 1);
    }
    if (getCaseMorpion(game, 0, 0)==getCaseMorpion(game, 1, 1)&&getCaseMorpion(game, 0, 0)==getCaseMorpion(game, 2, 2)&&getCaseMorpion(game, 1, 1)!=' '){
        return getCaseMorpion(game, 1, 1);
    }
    return ' ';
}
struct coup_t meilleurCoup(struct morpion_t *game, struct player_t *p){
    struct coup_t c;
    if (getPlayerType(p)==CROIX){
        int maxEval = -1000;
        for (int i = 0; i<MAX_L; i++){
            for (int j = 0; j<MAX_C; j++){
                if (movOK(game, i, j)){
                    setCaseMorpion(game, i, j, 'X');
                    int eval = minimax(game, 0, ROND);
                    setCaseMorpion(game, i, j, ' ');
                    if (maxEval<eval){
                        maxEval = eval;
                        c.x=i;
                        c.y=j;
                    }
                }
            }
        }
    }

    else {
        int minEval = 1000;
        for (int i = 0; i<MAX_L; i++){
            for (int j = 0; j<MAX_C; j++){
                if (movOK(game, i, j)){
                    setCaseMorpion(game, i, j, 'O');
                    int eval = minimax(game, 0, CROIX);
                    setCaseMorpion(game, i, j, ' ');
                    if (minEval>eval){
                        minEval = eval;
                        c.x=i;
                        c.y=j;
                    }
                }
            }
        }
    }
    return c;
}