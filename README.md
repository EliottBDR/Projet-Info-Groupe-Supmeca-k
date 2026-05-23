PUISSANCE 5


Règles du jeu

1.  Les joueurs jouent chacun leur tour
2.  Le joueur choisit une colonne où faire tomber sa pièce 
3.  Il choisit ensuite une zone de rotation (3×3 ou 5×5 aléatoirement) autour d'un pivot, qui doit contenir la pièce qu'il vient de poser
4.  Il choisit le sens de rotation : horaire ou anti-horaire 
5.  Après la rotation, la gravité est réappliquée 
6.  Le premier joueur à aligner 5 pièces gagne
7.  Si le plateau est plein sans vainqueur : match nul

Particularités

- Les 4 coins du plateau sont occupés par des blocs indestructibles (résistants à la rotation et à la gravité)
- Si il y a une victoire simultané de plusieurs joueurs après une rotation, c'est égalité 


Compiler le projet:

make

lancer le jeu:  

./game


Structure des fichiers

main.c          # Boucle principale, menus, animations
board.c / .h    # Plateau de jeu (initialisation, affichage)
gravity.c / .h  # Gravité (chute des pièces, colonne pleine)
rotation.c / .h # Rotation de zone (pivot, validation, application)
player.c / .h   # Gestion des joueurs et de l'état de la partie
win.c / .h      # Détection de victoire ou d'égalité
save.c / .h     # Sauvegarde et chargement de partie
Makefile

Sauvegarde

- Le jeu propose de sauvegarder à la fin de chaque tour
- La sauvegarde est stockée dans un fichier binaire sauvegarde.bin

Joueurs et symboles

              symbole       couleur
           
joueur 1 :       >           jaune 

joueur 2 :       (           cyan

joueur 3 :       [          magenta
