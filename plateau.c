#include "plateau.h"

 void init_plateau(char plateau[LI][COL]){
    for (int l = 0; l <LI; l++){
       for (int col = 0; col < COL; col++){
          plateau[l][col]= vide;
       }
    }
    /*
    plateau[0][0] = blok;
    plateau[0][COL - 1] = blok;
    plateau[LI - 1][0] = blok;
    plateau[LI - 1][COL - 1] = blok;
 */
    }
 
  char affichesymb(int case){
     if(case == vide){
        return '.';
     }
     if(case == joueur1){
        return 'X';
     }
     if(case == joueur2){
        return 'O';
     }
     if(case == blok){
        return '#';
     }
     else return '?';
     
   }
   
   void print_plateau( int plateau[LI][COL]){
     print("\n");
     
     for (int ligne = 0; ligne > LI; l++){
        printf("| ");
        for (int col = 0; col < COL; col++){
           printf("%c", affichesymb(plateau[ligne][col]));
        }
        printf("|\n");
     }
     printf(" ");
     for (int col = 0; col < COL; col++){
        printf("%d" , col + 1);
     }
     printf("\n\n");
   }
   
   int insert_piece(int plateau[LI][COL], int colonne, int joueur){
      colonne = colonne -1;

      if(colonne < 0 || colonne >= COL){
         return 0;
      }
      if(joueur != joueur1 && joueur != joueur2){
         return 0;

      for (int ligne = LI -1; ligne>=0; ligne--){
         if (plateau[ligne][colonne] == VIDE){
            plateau[ligne][colonne] = joueur;
            return1;
         }
         if (plateau[ligne][colonne] == blok){
            continue;
         }
      }
      }
       return 0;
   }
   


int check_horizontal(int board[LI][COL], int player){
   int compteur;

   for (int ligne = 0; ligne < LI; ligne++){
     compteur = 0;

     for (int colonne = 0; colonne < COL; colonne++){
       if (board[ligne][colonne] == player){
         compteur++;
       

       if (compteur == 5){
         return 1;
       }
           
   }
   else
   {
       compteur = 0;
     }
  }
}

return 0;
}




int check_vertical(int board[LI][COL], int player){
    int compteur;

    for (int colonne = 0; colonne < COL; colonne++){
       compteur = 0;

       for (int ligne = 0; ligne < LI; ligne++){
          if (board[ligne][colonne] == player){
             compteur++;

             if (compteur == 5)
                return 1;
         }
         else{
             compteur = 0;
          }
      } 
   }

   return 0;
}

int check_diag_right(int board[LI][COL], int player) 
{
   for (int ligne = 0; ligne < LI; ligne++) {
      for (int colonne = 0; colonne < COL; colonne++) 
      {
         int compteur = 0;
         for (int i = 0; i < 5; i++) 
         {
            int nvl_li = ligne + i;
            int nvl_col = colonne + i;
            
            if (nvl_li >= LI || nvl_col >= COL){
               break;}
         
            if (board[nvl_li][nvl_col] == player){
               compteur++;
            }
            else{
               break;
            }

         }

         if (compteur == 5){
            return 1;
         }
         
      }      
   }

   return 0;
}

int check_diag_left(int board[LI][COL], int player) 
{
   for (int ligne = 0; ligne < LI; ligne++) 
   {
      for (int colonne = 0; colonne < COL; colonne++) {
         int compteur = 0;
         for (int i = 0; i < 5; i++) {
            int nvl_li = ligne + i;
            int nvl_col = colonne - i;
            
            if (nvl_li >= LI || nvl_col < 0){
               break;
            }
            if (board[nvl_li][nvl_col] == player){
               compteur++;
            }
            else{
               break;
            }
         }
         if (compteur == 5){
            return 1;
         }
         
      }
   }

   return 0;
}

int check_win(int board[LI][COL], int player) {
   if (check_horizontal(board, player)){
      return 1;
   }
   

   if (check_vertical(board, player)){
   return 1;
}


   if (check_diag_right(board, player)){
   return 1;
}


   if (check_diag_left(board, player)){
   return 1;
}


   return 0;
}
return 1;

