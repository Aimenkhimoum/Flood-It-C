================================================================================
                              PROJET FLOOD-IT 
================================================================================

AUTEUR : KHIMOUM Aimen Mohamed 

1. DESCRIPTION DU PROJET
--------------------------------------------------------------------------------
Ce projet a pour objectif d'implémenter et d'analyser différentes stratégies
algorithmiques pour résoudre le jeu Flood-It. Le but du jeu est 
d'inonder une grille de dimensions NxN avec une seule couleur en un nombre 
minimal de coups, en partant de la zone supérieure gauche.

J'ai implémenté plusieurs versions, allant d'une approche naïve (aléatoire) à
des approches déterministes basées sur le gain immédiat (Max-Bordure) et
optimisées (Max-Bordure-Zone), pour finir par une stratégie d'anticipation.
Ce rapport présente l'analyse de mes résultats, les difficultés rencontrées et
une comparaison détaillée des performances.

2. ANALYSE DES STRATÉGIES ET RÉSULTATS
--------------------------------------------------------------------------------
- Algorithme 1 (Récursif) : Utilise une approche récursive pour identifier la
  zone Zsg. Provoque un Stack Overflow (dépassement de pile) sur des
  grilles dépassant 300x300 car la profondeur de récursion sature la mémoire
  allouée à la pile.
- Algorithme 2 (Itératif / Rapide) : Utilise le tas via des listes chaînées
  (ListeCase), permettant de traiter des grilles 1000x1000 sans plantage.
- Algorithme 3 (Max-Bordure) : Stratégie déterministe qui réduit drastiquement
  le nombre total de coups, mais qui prend du temps à scanner la 
  bordure à chaque tour.
- Algorithme 4 (Max-Bordure-Zone) : Stratégie plus intelligente qui compte toute
  la tache de couleur connectée à la bordure. Elle privilégie les
  couleurs qui ouvrent de grandes zones, offrant un nombre de coups
  joués systématiquement inférieur à l'algorithme 3.
- Algorithme 5 (Estimation) : Simule l'inondation virtuelle avec un marqueur
  spécial (VISITE_SIMU=-9) pour estimer le gain réel sans modifier
  définitivement la grille. Offre le nombre de coups le plus 
  optimal parmi toutes les stratégies testées.

3. DIFFICULTÉS RENCONTRÉES
--------------------------------------------------------------------------------
- Gestion de la mémoire : Rigueur particulière pour éviter les fuites de mémoire
  (free) lors de la manipulation des listes chaînées et la destruction des listes
  de bordures à chaque tour.
- Compilation multiple : Création d'un Makefile modulaire pour gérer le jeu
  principal et les différents tests de performance.

4. INSTALLATION ET COMPILATION
--------------------------------------------------------------------------------
Clonez le dépôt sur votre machine locale, puis entrez dans le dossier :
git clone https://github.com/Aimenkhimoum/Flood-It-C.git

cd Flood-It-C

Utilisez le Makefile fourni pour compiler le jeu et les tests:
- Pour tout compiler : make 
- Pour le jeu seul : make FloodIt 
- Pour les tests de performance : make Test_Temps Test_Strategies comp_exo2_exo3 

5. EXÉCUTION DU JEU
--------------------------------------------------------------------------------
Pour lancer une partie, utilisez la commande suivante :
./Flood-It <dim> <nbcl> <difficulte> <graine> <algo> <aff> 

Exemple : 
./FloodIt 500 10 2 20 3 1 
(Taille 500, 10 couleurs, difficulté 2, graine 20, Algo Max-Bordure (exo 3), 
Affichage activé) 

Codes Algorithmes :
[cite_start]1 = Récursif, 2 = Rapide, 3 = Max-Bordure, 4 = Max-Bordure-Zone, 5 = Estimation 

6. GÉNÉRATION DES COURBES
--------------------------------------------------------------------------------
Pour reproduire les courbes présentes dans ce rapport:
- Exécutez les scripts de test : ./Test_Temps, ./comp_exo2_exo3, ./Test_Strategies 
- Lancez les scripts Gnuplot : gnuplot courbes.gp, gnuplot comparaison2.gp, gnuplot plot_strategies.gp 
- Les images .png seront générées dans le dossier du projet.