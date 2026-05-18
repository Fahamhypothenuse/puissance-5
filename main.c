#include <stdio.h>
#include "plateau.h"

int main(void){
int plateau[LI][COL];
int player = PLAYER_1;
int colonne;
int reussite;

init_plateau(plateau);

while (1){
print_plateau(plateau);

printf("Joueur %d, choisissez une colonne: ", player);
scanf("%d", &colonne);

reussite = insert_piece(plateau, colonne, player);

if (reussite == 0){
printf("Invalide. reessayez.\n");
continue;
}

if (player == joueur1){

player = joueur2;
else
player = joueur2;
}
}
return 0;
}