#ifndef PLAYER_H
#define PLAYER_H
//include
#include "show.h"
//MACROS
#define MAX_PLAYERS 2

enum typePlayer_t {
    CROIX=0,
    ROND,
    TIE
};

struct player_t;

enum typePlayer_t getChoixPlayer(struct player_t *p);
void setPosPlayer(struct player_t *p, int l, int c);
enum typePlayer_t getPlayerType(struct player_t *p);
enum typePlayer_t switchPlayer(enum typePlayer_t p);
struct player_t * choixPlayer(struct player_t * p1, struct player_t * p2, enum typePlayer_t p);
struct player_t * initPlayer(enum typePlayer_t p);
int isPlayerWin(struct player_t *p1);
#endif //PLAYER_H