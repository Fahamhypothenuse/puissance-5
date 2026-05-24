#ifndef SAVE_H
#define SAVE_H

#include "board.h"

/* Sauvegardede la partie dans un fichier texte.
   Retourne 1 si OK 0 sinon */

int save_game(char board[ROWS][COLS], int current_player);
int load_game(char board[ROWS][COLS], int *current_player);

#endif
