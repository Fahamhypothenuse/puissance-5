#include "board.h"
#include "save.h"
#include <unistd.h>  /* pour la fonction sleep() */

/* Vide le buffer d'entree */
int vider_buffer(void) {
    int ch;
    while ((ch = getchar()) != '\n') {
        if (ch == EOF) return 0;
    }
    return 1;
}

/* Donne un exemple de pivot valide pour aider le joueur. */
void exemple_pivot(int piece_row, int piece_col, int zone_size,
                   int *ex_row, int *ex_col) {
    int offset = zone_size / 2;
    /* On essaie de prendre la piece elle meme comme pivot.
       Si ca ne tient pas dans le plateau, on ajuste. */
    int pr = piece_row;
    int pc = piece_col;
    /* Ajustements pour rester dans les bornes */
    if (pr - offset < 0) pr = offset;
    if (pc - offset < 0) pc = offset;
    if (pr + offset >= ROWS) pr = ROWS - 1 - offset;
    if (pc + offset >= COLS) pc = COLS - 1 - offset;

    *ex_row = pr + 1; 
    *ex_col = pc + 1;
}

int main(void){
    char board[ROWS][COLS];
    int player = PLAYER1;
    int column;
    int p_row;
    int p_col;
    int zone_size;
    int direction;
    int piece_row;
    int piece_col;
    int menu_choice;
    time_t start_time;
    int elapsed;

    /* srand on l'initialise une seule fois au debut */
    srand(time(NULL));

    
    printf(COLOR_YELLOW "=== CY-CONNECT ===" COLOR_RESET "\n");
    printf("1. Nouvelle partie\n");
    printf("2. Charger une partie sauvegardee\n");
    printf("Votre choix : ");
    if (scanf("%d", &menu_choice) != 1) {
        if (feof(stdin)) return 0;
        menu_choice = 1;
    }
    if (!vider_buffer()) return 0;

    if (menu_choice == 2) {
        if (load_game(board, &player)) {
            printf("Partie chargee. C'est au joueur %d de jouer.\n", player);
        } else {
            printf("Pas de sauvegarde valide. Nouvelle partie.\n");
            init_board(board);
            player = PLAYER1;
        }
    } else {
        init_board(board);
    }

    /* Demarrage du chrono */
    start_time = time(NULL);

    /*Boucle principale*/
    while (1){
    
        if (rand() % 2 == 0) {
            zone_size = 3;
        } else {
            zone_size = 5;
        }

        print_board(board);

        /* Affichage du temps ecoule */
        elapsed = (int)difftime(time(NULL), start_time);
        printf(COLOR_YELLOW "Temps : %d:%02d" COLOR_RESET "\n",
               elapsed / 60, elapsed % 60);

        printf("Joueur %d, taille de la zone qui sera pivotee : %dx%d\n",
               player, zone_size, zone_size);
        printf("Tapez 0 pour sauvegarder et quitter.\n");
        printf("Joueur %d, choisissez une colonne (1 a 8) : ", player);

        if (scanf("%d", &column) != 1) {
            if (feof(stdin)) return 0;
            if (!vider_buffer()) return 0;
            printf("Saisie invalide. Tapez un nombre entre 1 et 8.\n");
            printf("(Patientez 2 secondes...)\n");
            sleep(2);
            continue;
        }
        if (!vider_buffer()) return 0;

        /* Option de sauvegarde */
        if (column == 0) {
            if (save_game(board, player)) {
                printf("Partie sauvegardee dans 'partie.txt'. A bientot !\n");
            } else {
                printf("Erreur lors de la sauvegarde.\n");
            }
            return 0;
        }

        /* Insertion de la piece */
        if (!insert_piece(board, column, player, &piece_row, &piece_col)){
            printf("Coup invalide (colonne hors limite ou pleine). Reessayez.\n");
            printf("(Patientez 2 secondes...)\n");
            sleep(2);
            continue;
        }

        /* Affichage etape apres insertion */
        printf("\n");
        printf(COLOR_YELLOW "========== ETAPE 1/3 : APRES INSERTION ==========" COLOR_RESET);
        print_board(board);
        sleep(1);

        /* Choix du pivot et du sens */
        int rotation_ok = 0;
        while (rotation_ok == 0) {
            /* Calculer un exemple de pivot valide pour aider */
            int ex_row, ex_col;
            exemple_pivot(piece_row, piece_col, zone_size, &ex_row, &ex_col);

            printf("\n");
            printf("Votre piece est en " COLOR_RED "ligne %d, colonne %d" COLOR_RESET ".\n",
                   piece_row + 1, piece_col + 1);
            printf("La zone de %dx%d doit CONTENIR votre piece.\n", zone_size, zone_size);
            printf("Exemple de pivot valide : ligne %d colonne %d\n", ex_row, ex_col);
            printf("Joueur %d, entrez la ligne et la colonne du PIVOT : ", player);

            if (scanf("%d %d", &p_row, &p_col) != 2) {
                if (feof(stdin)) return 0;
                if (!vider_buffer()) return 0;
                printf("Saisie invalide. Tapez 2 nombres (ex: 3 4).\n");
                sleep(2);
                continue;
            }
            if (!vider_buffer()) return 0;

            printf("Sens (1 = Horaire, 0 = Anti-horaire) : ");
            if (scanf("%d", &direction) != 1) {
                if (feof(stdin)) return 0;
                if (!vider_buffer()) return 0;
                printf("Saisie invalide. Tapez 0 ou 1.\n");
                sleep(2);
                continue;
            }
            if (!vider_buffer()) return 0;

            int c_row = p_row - 1;  
            int c_col = p_col - 1;

            if (!valid_zone(c_row, c_col, zone_size)) {
                printf("Zone invalide : avec ce pivot, la zone %dx%d sort du plateau.\n",
                       zone_size, zone_size);
                sleep(2);
                continue;
            }
            if (!zone_contains_piece(c_row, c_col, zone_size,
                                     piece_row, piece_col)) {
                printf("Zone invalide : la zone doit contenir la piece que vous venez de poser.\n");
                sleep(2);
                continue;
            }

            rotate_zone(board, c_row, c_col, zone_size, direction);
            rotation_ok = 1;
        }

        /* Affichage etape 2 apres rotation */
        printf("\n");
        printf(COLOR_YELLOW "========== ETAPE 2/3 : APRES ROTATION ==========" COLOR_RESET);
        print_board(board);
        sleep(1);

        /* Etape 3 gravite */
        apply_gravity(board);
        printf("\n");
        printf(COLOR_YELLOW "========== ETAPE 3/3 : APRES GRAVITE (etat final) ==========" COLOR_RESET);
        print_board(board);
        sleep(1);

        /* on teste les 2 joueurs apres la rotation
           (egalite possible si les 2 alignent 5 en meme temps) */
        int p1_wins = check_win(board, PLAYER1);
        int p2_wins = check_win(board, PLAYER2);

        if (p1_wins || p2_wins) {
            elapsed = (int)difftime(time(NULL), start_time);

            printf("\n");
            if (p1_wins && p2_wins) {
                printf(COLOR_YELLOW "========== EGALITE Les deux joueurs ont aligne 5 pieces ! ========== " COLOR_RESET "\n");
            } else if (p1_wins) {
                printf(COLOR_RED "========== Le joueur 1 (X) gagne la partie  Bravo ! ==========" COLOR_RESET "\n");
            } else {
                printf(COLOR_BLUE "Le joueur 2 (O) gagne la partie  Bravo ! " COLOR_RESET "\n");
            }
            printf(COLOR_YELLOW "Duree de la partie : %d:%02d" COLOR_RESET "\n",
                   elapsed / 60, elapsed % 60);
            break;
        }

        /* Changement de joueur */
        if (player == PLAYER1){
            player = PLAYER2;
        } else {
            player = PLAYER1;
        }
    }

    return 0;
}