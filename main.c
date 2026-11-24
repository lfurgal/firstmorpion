#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

// Inclusion des headers
#include "move.h"
#include "player.h"
#include "show.h"
#include "solver.h"

// Fonction d'affichage spécifique pour ncurses
void showMorpionNcurses(struct morpion_t *jeu, int cursor_y, int cursor_x) {
    clear(); // Efface l'écran du terminal
    printw("=== JEU DU MORPION ===\n\n");
    printw("Utilisez les FLECHES pour vous deplacer, ESPACE/ENTREE pour valider.\n\n");
    printw("  (X = Rouge | O = Vert)\n\n");

    for (int i = 0; i < MAX_L; i++) {
        printw("  +---+---+---+\n  |");
        for (int j = 0; j < MAX_C; j++) {
            char c = getCaseMorpion(jeu, i, j);
            // Surligne la case si le curseur est dessus
            int color_pair = 0;
            if (c == 'X') color_pair = 1;      // Paire 1 = Rouge
            else if (c == 'O') color_pair = 2; // Paire 2 = Vert

            // Gestion de l'affichage avec curseur (surligné) et couleur
            if (i == cursor_y && j == cursor_x) {
                attron(A_REVERSE | COLOR_PAIR(color_pair));
                printw(" %c ", c);
                attroff(A_REVERSE | COLOR_PAIR(color_pair));
            } else {
                if (color_pair) attron(COLOR_PAIR(color_pair));
                printw(" %c ", c);
                if (color_pair) attroff(COLOR_PAIR(color_pair));
            printw("|");
            }
        }
        printw("\n");
    }
    printw("  +---+---+---+\n\n");
    refresh();
}

int main(int argc, char *argv[]){
    // --- 1. INITIALISATION NCURSES ---
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    // Demande du mode de jeu (avant ncurses ou proprement dedans, ici dans ncurses)
    printw("Tapez 1 pour jouer en solo (vs Ordinateur) ou 2 pour jouer à deux : ");
    refresh();
    
    int nbJoueur = 1;
    char choix_char = getch();
    if (choix_char == '2') nbJoueur = 2;

    int IS_NOT_WIN = 1;
    struct morpion_t* gameCouranteMorpion = initMorpion();
    struct player_t* p1 = initPlayer(CROIX);
    struct player_t* p2 = initPlayer(ROND);
    int n = 0;
    enum typePlayer_t pCourant = CROIX;

    int cursor_y = 0, cursor_x = 0;
    int i = 0, j = 0;

    while (n < MAX_TOURS && IS_NOT_WIN){
        struct player_t *pNow = choixPlayer(p1, p2, pCourant);

        // --- TOUR DU JOUEUR HUMAIN ---
        if (nbJoueur == 2 || (nbJoueur == 1 && pCourant == CROIX)){
            int coup_valide = 0;
            while (!coup_valide) {
                showMorpionNcurses(gameCouranteMorpion, cursor_y, cursor_x);
                printw("Tour de %s\n", (pCourant == CROIX) ? "CROIX (X)" : "ROND (O)");
                
                int ch = getch();
                if (ch == KEY_UP && cursor_y > 0) cursor_y--;
                else if (ch == KEY_DOWN && cursor_y < MAX_L - 1) cursor_y++;
                else if (ch == KEY_LEFT && cursor_x > 0) cursor_x--;
                else if (ch == KEY_RIGHT && cursor_x < MAX_C - 1) cursor_x++;
                else if (ch == '\n' || ch == ' ') {
                    if (movOK(gameCouranteMorpion, cursor_y, cursor_x)) {
                        i = cursor_y;
                        j = cursor_x;
                        coup_valide = 1;
                    } else {
                        printw("Case deja occupee !\n");
                        refresh();
                        getch();
                    }
                }
            }
        } 
        // --- TOUR DE L'IA ---
        else {
            showMorpionNcurses(gameCouranteMorpion, -1, -1);
            printw("L'ordinateur réfléchit...\n");
            refresh();
            
            struct coup_t coup = meilleurCoup(gameCouranteMorpion, p2);
            i = coup.x;
            j = coup.y;
        }

        // Application du coup
        movePlateau(pNow, gameCouranteMorpion, i, j);
        ++n;

        // Vérification de fin de partie
        char gagnant = gagnantMorpion(gameCouranteMorpion);
        if (gagnant != ' ' || isGrillePleine(gameCouranteMorpion)) {
            IS_NOT_WIN = 0;
        }

        pCourant = switchPlayer(pCourant);
    }

    // --- ÉCRAN DE FIN ---
    showMorpionNcurses(gameCouranteMorpion, -1, -1);
    char gagnantFinal = gagnantMorpion(gameCouranteMorpion);
    if (gagnantFinal == 'X') {
        printw("Victoire des CROIX (X) !\n");
    } else if (gagnantFinal == 'O') {
        printw("Victoire des RONDS (O) !\n");
    } else {
        printw("Match nul !\n");
    }
    
    printw("\nAppuyez sur une touche pour quitter...");
    refresh();
    getch();

    // --- NETTOYAGE NCURSES ET MEMOIRE ---
    endwin();
    free(gameCouranteMorpion);
    free(p1);
    free(p2);
    return 0;
}