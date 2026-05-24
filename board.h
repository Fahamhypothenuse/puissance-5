#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define EMPTY 0
#define COLS 8
#define ROWS 6
#define PLAYER1 1
#define PLAYER2 2
#define BLOCK 9

/* Couleurs ANSI pour l'affichage colore dans le terminal */
#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[1;31m"
#define COLOR_BLUE    "\033[1;34m"
#define COLOR_WHITE   "\033[1;37m"
#define COLOR_YELLOW  "\033[1;33m"

void init_board(char board[ROWS][COLS]);
void print_board(char board[ROWS][COLS]);

/* insert_piece pose une piece dans la colonne 
   Stocke la position finale dans piece_row et piece_col. */
int insert_piece(char board[ROWS][COLS], int column, int player,
                 int *piece_row, int *piece_col);

int valid_zone(int pivot_row, int pivot_col, int size);

/* Verifie que la zone englobe bien la piece  */
int zone_contains_piece(int pivot_row, int pivot_col, int size,
                        int piece_row, int piece_col);

void rotate_zone(char board[ROWS][COLS], int pivot_row, int pivot_col,
                 int size, int clockwise);
void apply_gravity(char board[ROWS][COLS]);

int check_win(char board[ROWS][COLS], int player);

#endif
