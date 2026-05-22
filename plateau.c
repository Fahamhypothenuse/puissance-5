
#include "plateau.h"

void init_plateau(char plateau[LI][COL]){
    for (int l = 0; l < LI; l++){
       for (int col = 0; col < COL; col++){
          plateau[l][col] = VIDE;
       }
    }
    plateau[0][0] = blok;
    plateau[0][COL - 1] = blok;
    plateau[LI - 1][0] = blok;
    plateau[LI - 1][COL - 1] = blok;
}
 
char affichesymb(int c){
    if(c == VIDE) return '.';
    if(c == joueur1) return 'X';
    if(c == joueur2) return 'O';
    if(c == blok) return '#';
    return '?';
}
   
void print_plateau(char plateau[LI][COL]){
    printf("\n");
    for (int ligne = 0; ligne < LI; ligne++){
       printf("| ");
       for (int col = 0; col < COL; col++){
          printf("%c ", affichesymb(plateau[ligne][col]));
       }
       printf("|\n");
    }
    printf("  ");
    for (int col = 0; col < COL; col++){
       printf("%d ", col + 1);
    }
    printf("\n\n");
}
   
int insert_piece(char plateau[LI][COL], int colonne, int joueur){
    colonne = colonne - 1;

    if(colonne < 0 || colonne >= COL){
       return 0;
    }
    if(joueur != joueur1 && joueur != joueur2){
       return 0;
    }

    if (plateau[0][colonne] != VIDE) {
       return 0; 
    }

    
    for (int ligne = 0; ligne < LI; ligne++) {
       
       if (ligne == LI - 1 || plateau[ligne + 1][colonne] != VIDE) {
          plateau[ligne][colonne] = joueur;
          return 1; 
       }
    }
    
    return 0;
}
   
int check_horizontal(char board[LI][COL], int player){
   int compteur;
   for (int ligne = 0; ligne < LI; ligne++){
      compteur = 0;
      for (int colonne = 0; colonne < COL; colonne++){
         if (board[ligne][colonne] == player){
            compteur++;
            if (compteur == 5){
               return 1;
            }
         } else {
            compteur = 0;
         }
      }
   }
   return 0;
}

int check_vertical(char board[LI][COL], int player){
    int compteur;
    for (int colonne = 0; colonne < COL; colonne++){
       compteur = 0;
       for (int ligne = 0; ligne < LI; ligne++){
          if (board[ligne][colonne] == player){
             compteur++;
             if (compteur == 5) return 1;
          } else {
             compteur = 0;
          }
       } 
    }
    return 0;
}

int check_diag_right(char board[LI][COL], int player) {
   for (int ligne = 0; ligne < LI; ligne++) {
      for (int colonne = 0; colonne < COL; colonne++) {
         int compteur = 0;
         for (int i = 0; i < 5; i++) {
            int nvl_li = ligne + i;
            int nvl_col = colonne + i;
            
            if (nvl_li >= LI || nvl_col >= COL) break;
         
            if (board[nvl_li][nvl_col] == player) compteur++;
            else break;
         }
         if (compteur == 5) return 1;
      }      
   }
   return 0;
}

int check_diag_left(char board[LI][COL], int player) {
   for (int ligne = 0; ligne < LI; ligne++) {
      for (int colonne = 0; colonne < COL; colonne++) {
         int compteur = 0;
         for (int i = 0; i < 5; i++) {
            int nvl_li = ligne + i;
            int nvl_col = colonne - i;
            
            if (nvl_li >= LI || nvl_col < 0) break;
            
            if (board[nvl_li][nvl_col] == player) compteur++;
            else break;
         }
         if (compteur == 5) return 1;
      }
   }
   return 0;
}

int check_win(char board[LI][COL], int player) {
   if (check_horizontal(board, player)) return 1;
   if (check_vertical(board, player)) return 1;
   if (check_diag_right(board, player)) return 1;
   if (check_diag_left(board, player)) return 1;
   return 0;
}

int zone_valide(int pivot_LI, int pivot_COL, int size) {
    int offset = size / 2;
    int debut_LI = pivot_LI - offset;
    int debut_COL = pivot_COL - offset;
 
    if (debut_LI < 0 || debut_COL < 0) {
        return 0;
    }

    if ((debut_LI + size) > LI || (debut_COL + size) > COL) {
        return 0; 
    }

    return 1;
}


void rotation_zone(char plateau[LI][COL], int pivot_LI, int pivot_COL, int size, int sens_horloge) {
    int offset = size / 2;
    int debut_LI= pivot_LI - offset;
    int debut_COL = pivot_COL - offset;
    int temp[size][size];
    
    srand(time(NULL));


    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            temp[i][j] = plateau[debut_LI + i][debut_COL + j];
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (sens_horloge) {
                plateau[debut_LI + j][debut_COL + (size - 1 - i)] = temp[i][j];
            } else {
                plateau[debut_LI + (size - 1 - j)][debut_COL + i] = temp[i][j];
            }
        }
    }
}

void appliquer_gravite(char plateau[LI][COL]) {
    for (int j = 0; j < COL; j++) {
        
        for (int etape = 0; etape < LI; etape++) {
            for (int i = LI - 2; i >= 0; i--) {
                
                if (plateau[i][j] != VIDE && plateau[i][j] != 'I' && plateau[i][j] != blok) { 
                    if (plateau[i + 1][j] == VIDE) {
                        plateau[i + 1][j] = plateau[i][j]; 
                        plateau[i][j] = VIDE;              
                    }
                }
            }
        }
    }
}
