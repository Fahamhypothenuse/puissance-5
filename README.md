Projet Pré-Ing1 CY-Connect

Salhi Ilies
Diarra Oumar
Boina Fahami

Description;

Jeu à 2 joueurs sur un plateau 8 colonnes x 6 lignes. Chaque joueur place une
pièce en haut d'une colonne, la pièce tombe par gravité. Ensuite le joueur
doit choisir une zone carrée (3x3 ou 5x5) du plateau qui contient sa pièce
et la faire pivoter de 90 degres (horaire ou anti-horaire). La gravité s'applique
à nouveau. Le but est d'aligner 5 pièces (horizontalement, verticalement ou
en diagonale).

Les 4 coins du plateau sont des blocs indestructibles, insensibles à la gravité
mais déplaçables par les rotations.

Compilation:

Entrez "make" dans le terminale puis pour lancer "./exec"

Menu de démarrage:

Au lancement, choisir :
`1` pour démarrer une nouvelle partie
`2` pour charger une partie sauvegardée 

Pendant la partie:

À chaque tour, le programme :
1. Affiche le plateau (numéros de ligne à gauche, numéros de colonne en bas)
2. Annonce la taille de la zone qui devra être pivotée (3x3 ou 5x5, tirée
   au hasard)
3. Demande au joueur de choisir une colonne (de 1 à 8)
4. Demande de choisir un pivot (ligne et colonne) puis un sens de rotation
   (1 = horaire, 0 = anti-horaire)

La pièce posée doit obligatoirement se trouver dans la zone à pivoter. Le
programme propose un exemple de pivot valide pour aider le joueur.

Sauvegarder en cours de partie:

À n'importe quel moment, quand on vous demande une colonne, taper `0` au
lieu d'un numéro de colonne. La partie est sauvegardée dans `partie.txt`
et le programme se ferme. Au prochain lancement, choisir `2` dans le menu
pour reprendre.

Symboles à l'écran:

`X` (rouge)  : pièce du joueur 1
`O` (bleu)   : pièce du joueur 2
`#` (blanc)  : bloc indestructible
-`.`         : case vide

Structure:

board.h / board.c : gestion du plateau (init, affichage, insertion,
rotation, gravité, détection de victoire)
save.h / save.c   : sauvegarde et chargement de partie
main.c              : programme principal et boucle de jeu
Makefile            : compilation

