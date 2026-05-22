

int main(void){
    char plateau[LI][COL];
    int player = joueur1;
    int colonne;
    int reussite;
    int p_ligne; 
    int p_col;
    int taille_zone;
    int sens;

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

        
        int rotation_ok = 0;

        if (rand() % 2 == 0) {
            taille_zone = 3;
        } else {
            taille_zone = 5;
        }

        while (rotation_ok == 0) {
            print_plateau(plateau); 
            printf("ON VA FAIRE PIVOTER CE PLATEAU 😈😈 ! Vous devez faire une rotation de taille : %dx%d\n", taille_zone, taille_zone);
            printf("Joueur %d, entrez la ligne et la colonne du PIVOT (ex: 3 4): ", player);
            if (scanf("%d %d", &p_ligne, &p_col) != 2) {
                while(getchar() != '\n');
                continue;
            }

            printf("Entrez le sens (1 pour Horaire, 0 pour Anti-horaire): ");
            if (scanf("%d", &sens) != 1) {
                while(getchar() != '\n');
                continue;
            }
            while(getchar() != '\n'); 

            int c_ligne = p_ligne - 1;
            int c_col = p_col - 1;

            if (zone_valide(c_ligne, c_col, taille_zone)) {
                rotation_zone(plateau, c_ligne, c_col, taille_zone, sens);
                rotation_ok = 1; 
                
                appliquer_gravite(plateau);
            } else {
                printf(" Zone invalide avec un pivot pour du %dx%d ! Ça depasse du plateau. Reessayez.\n", taille_zone, taille_zone);
            }
        }

        if (check_win(plateau, player)) {
            print_plateau(plateau);
            printf("FIN DE LA PARTIE ! Le joueur %d a gagne la partie !!!!!! BRAVO !👏👏👏👏 \n", player);
            break; 
        }


        if (player == joueur1){
            player = joueur2;
        } else {
            player = joueur1;
        }

    
    
}
return 0;
}
