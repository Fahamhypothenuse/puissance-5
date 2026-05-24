#include "board.h"

void init_board(char board[ROWS][COLS]){
    for (int r = 0; r < ROWS; r++){
        for (int c = 0; c < COLS; c++){
            board[r][c] = EMPTY;
        }
    }
    /* Les 4 coins sont des blocs indestructibles */
    board[0][0] = BLOCK;
    board[0][COLS - 1] = BLOCK;
    board[ROWS - 1][0] = BLOCK;
    board[ROWS - 1][COLS - 1] = BLOCK;
}

void print_board(char board[ROWS][COLS]){
    printf("\n");
    for (int row = 0; row < ROWS; row++){
        /* Numero de ligne a gauche */
        printf(COLOR_YELLOW "%d " COLOR_RESET, row + 1);
        printf("| ");
        for (int col = 0; col < COLS; col++){
            int v = board[row][col];
            /* Affichage colore selon la valeur de la case */
            if (v == EMPTY) {
                printf(". ");
            } else if (v == PLAYER1) {
                printf(COLOR_RED "X " COLOR_RESET);
            } else if (v == PLAYER2) {
                printf(COLOR_BLUE "O " COLOR_RESET);
            } else if (v == BLOCK) {
                printf(COLOR_WHITE "# " COLOR_RESET);
            } else {
                printf("? ");
            }
        }
        printf("|\n");
    }
    /* Numerotation des colonnes en bas (4 espaces pour aligner) */
    printf("    ");
    for (int col = 0; col < COLS; col++){
        printf(COLOR_YELLOW "%d " COLOR_RESET, col + 1);
    }
    printf("\n\n");
}

int insert_piece(char board[ROWS][COLS], int column, int player,
                 int *piece_row, int *piece_col){
    column = column - 1;  /* l'utilisateur tape 1..8, on travaille en 0..7 */

    if (column < 0 || column >= COLS){
        return 0;
    }
    if (player != PLAYER1 && player != PLAYER2){
        return 0;
    }
    /* Si la case du haut est deja occupe on ne peut pas inserer */
    if (board[0][column] != EMPTY){
        return 0;
    }

    /* La piece descend tant que la case en dessous est vide */
    int row = 0;
    while (row < ROWS - 1 && board[row + 1][column] == EMPTY){
        row++;
    }
    board[row][column] = player;

    *piece_row = row;
    *piece_col = column;
    return 1;
}

int check_horizontal(char board[ROWS][COLS], int player){
    int counter;
    for (int row = 0; row < ROWS; row++){
        counter = 0;
        for (int col = 0; col < COLS; col++){
            if (board[row][col] == player){
                counter++;
                if (counter == 5){
                    return 1;
                }
            } else {
                counter = 0;
            }
        }
    }
    return 0;
}

int check_vertical(char board[ROWS][COLS], int player){
    int counter;
    for (int col = 0; col < COLS; col++){
        counter = 0;
        for (int row = 0; row < ROWS; row++){
            if (board[row][col] == player){
                counter++;
                if (counter == 5) return 1;
            } else {
                counter = 0;
            }
        }
    }
    return 0;
}

int check_diag_right(char board[ROWS][COLS], int player) {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            int counter = 0;
            for (int i = 0; i < 5; i++) {
                int new_row = row + i;
                int new_col = col + i;
                if (new_row >= ROWS || new_col >= COLS) break;
                if (board[new_row][new_col] == player) counter++;
                else break;
            }
            if (counter == 5) return 1;
        }
    }
    return 0;
}

int check_diag_left(char board[ROWS][COLS], int player) {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            int counter = 0;
            for (int i = 0; i < 5; i++) {
                int new_row = row + i;
                int new_col = col - i;
                if (new_row >= ROWS || new_col < 0) break;
                if (board[new_row][new_col] == player) counter++;
                else break;
            }
            if (counter == 5) return 1;
        }
    }
    return 0;
}

int check_win(char board[ROWS][COLS], int player) {
    if (check_horizontal(board, player)) return 1;
    if (check_vertical(board, player)) return 1;
    if (check_diag_right(board, player)) return 1;
    if (check_diag_left(board, player)) return 1;
    return 0;
}

int valid_zone(int pivot_row, int pivot_col, int size) {
    /* Le pivot doit etre dans le plateau */
    if (pivot_row < 0 || pivot_row >= ROWS) return 0;
    if (pivot_col < 0 || pivot_col >= COLS) return 0;

    int offset = size / 2;
    int start_row = pivot_row - offset;
    int start_col = pivot_col - offset;

    if (start_row < 0 || start_col < 0) {
        return 0;
    }
    if ((start_row + size) > ROWS || (start_col + size) > COLS) {
        return 0;
    }
    return 1;
}

/* La piece doit etre dans le carre centre sur le pivot */
int zone_contains_piece(int pivot_row, int pivot_col, int size,
                        int piece_row, int piece_col) {
    int offset = size / 2;
    if (piece_row < pivot_row - offset || piece_row > pivot_row + offset) return 0;
    if (piece_col < pivot_col - offset || piece_col > pivot_col + offset) return 0;
    return 1;
}

void rotate_zone(char board[ROWS][COLS], int pivot_row, int pivot_col,
                 int size, int clockwise) {
    int offset = size / 2;
    int start_row = pivot_row - offset;
    int start_col = pivot_col - offset;

    /* On copie d'abord la zone dans temp pour ne pas ecraser les
       valeurs en cours de lecture pendant la rotation */
    char temp[size][size];

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            temp[i][j] = board[start_row + i][start_col + j];
        }
    }

    /* Formule de rotation :
        horaire: (i,j) -> (j, size-1-i)
        anti-horaire: (i,j) -> (size-1-j, i)  */
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (clockwise) {
                board[start_row + j][start_col + (size - 1 - i)] = temp[i][j];
            } else {
                board[start_row + (size - 1 - j)][start_col + i] = temp[i][j];
            }
        }
    }
}

void apply_gravity(char board[ROWS][COLS]) {
    /* On repete tant que des pieces tombent.
       Les BLOCK ne tombent pas */
    int moved = 1;
    while (moved) {
        moved = 0;
        for (int i = ROWS - 2; i >= 0; i--) {
            for (int j = 0; j < COLS; j++) {
                if (board[i][j] != EMPTY && board[i][j] != BLOCK) {
                    if (board[i + 1][j] == EMPTY) {
                        board[i + 1][j] = board[i][j];
                        board[i][j] = EMPTY;
                        moved = 1;
                    }
                }
            }
        }
    }
}
