#include "save.h"

/* Ce fichier sert a sauvegarder la partie dans un fichier
   "partie.txt" et a la recharger plus tard.

   Dans le fichier on ecrit :
   - le numero du joueur qui doit jouer (1 ou 2)
   - puis le plateau, case par case

   On utilise des chiffres pour representer les cases :
   0= case vide
   1 = piece du joueur 1 (X)
   2 = piece du joueur 2 (O)
   9 = bloc indestructible (#)
*/

int save_game(char board[ROWS][COLS], int current_player) {
    FILE *f = fopen("partie.txt", "w");
    if (f == NULL) return 0;

    fprintf(f, "%d\n", current_player);

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            char c;
            if (board[i][j] == EMPTY) c = '0';
            else if (board[i][j] == PLAYER1) c = '1';
            else if (board[i][j] == PLAYER2) c = '2';
            else c = '9'; 
            fputc(c, f);
        }
        fputc('\n', f);
    }
    fclose(f);
    return 1;
}

int load_game(char board[ROWS][COLS], int *current_player) {
    FILE *f = fopen("partie.txt", "r");
    if (f == NULL) return 0;

    int p;
    if (fscanf(f, "%d\n", &p) != 1) {
        fclose(f);
        return 0;
    }
    if (p != PLAYER1 && p != PLAYER2) {
        fclose(f);
        return 0;
    }

    /* Lecture des 6 lignes du plateau */
    for (int i = 0; i < ROWS; i++) {
        for (int k = 0; k < COLS; k++) {
            int c = fgetc(f);
            if (c == '0') board[i][k] = EMPTY;
            else if (c == '1') board[i][k] = PLAYER1;
            else if (c == '2') board[i][k] = PLAYER2;
            else if (c == '9') board[i][k] = BLOCK;
            else {
                /* caractere invalide on annule */
                fclose(f);
                return 0;
            }
        }
        fgetc(f);  /* on saute le '\n' en fin de ligne */
    }
    fclose(f);
    *current_player = p;
    return 1;
}
