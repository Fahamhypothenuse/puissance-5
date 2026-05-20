#include <stdio.h>
#include "plateau.h"

int main(void){
    char plateau[LI][COL];
    int player = joueur1;
    int colonne;
    int reussite;

    init_plateau(plateau);

    while (1){
        print_plateau(plateau);

        printf("Joueur %d, choisissez une colonne: ", player);
        
        if (scanf("%d", &colonne) != 1) {
            printf("Saisie invalide (chiffre uniquement).\n");
            while(getchar() != '\n'); 
            continue;
        }
        
        while(getchar() != '\n'); 

        reussite = insert_piece(plateau, colonne, player);

        if (reussite == 0){
            printf("Coup invalide. Reessayez.\n");
            continue;
        }

        if (player == joueur1){
            player = joueur2;
        } else {
            player = joueur1;
        }
    }
    
    return 0;
}
