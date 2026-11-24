#include <stdio.h>
#include <stdlib.h>
#include "show.h"


struct morpion_t {
    char tab[MAX_L][MAX_C];
};

struct morpion_t *initMorpion(){
    struct morpion_t *jeu = malloc(sizeof(struct morpion_t));
    int i = 0;
    while (i<MAX_L) {
        int j = 0;
        while (j<MAX_C) {
            jeu->tab[i][j]=' ';
            ++j;
        }
        ++i;
    }
    return jeu;
}
void showMorpion(struct morpion_t *jeu){
    int i = 0;
    while (i<MAX_L) {
        printf("|");
        int j = 0;
        while (j<MAX_C) {
            printf("%c|", jeu->tab[i][j]);
            ++j;
        }
        ++i;
        printf("\n");        
    }
}

char getCaseMorpion(struct morpion_t *jeu, int l, int c){
    return jeu->tab[l][c];
}
void setCaseMorpion(struct morpion_t *jeu, int l, int c, char sigle){
    jeu->tab[l][c]=sigle;
}


