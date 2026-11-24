#ifndef SHOW_H
#define SHOW_H

#define MAX_L 3
#define MAX_C 3
#define MAx_CASE 9

struct morpion_t;

struct morpion_t *initMorpion();
void showMorpion(struct morpion_t *jeu);
char getCaseMorpion(struct morpion_t *jeu, int l, int c);
void setCaseMorpion(struct morpion_t *jeu, int l, int c, char sigle);


#endif //SHOW_H