# Projet Flood-It

**Auteur :** KHIMOUM Aimen Mohamed  
**Dépôt :** [GitHub - Flood-It-C](https://github.com/Aimenkhimoum/Flood-It-C.git)

---

## Description du projet
L'objectif de ce projet est d'implémenter et d'analyser différentes stratégies algorithmiques pour résoudre le jeu **Flood-It**. 

**But du jeu :** Inonder une grille de dimensions $N \times N$ avec une seule couleur en un nombre minimal de coups, en partant de la zone supérieure gauche (Zsg). Le projet explore plusieurs approches, de la plus naïve à la plus optimisée (anticipation).

## Analyse des stratégies et résultats
J'ai implémenté 5 variantes algorithmiques pour répondre aux défis de performance et d'optimisation :

* **Algorithme 1 (Récursif) :** Approche directe pour identifier la zone Zsg. *Limite :* Provoque un **Stack Overflow** sur des grilles $> 300 \times 300$.
* **Algorithme 2 (Itératif / Rapide) :** Utilise le tas via des listes chaînées (`ListeCase`). Permet de traiter des grilles jusqu'à **1000x1000**.
* **Algorithme 3 (Max-Bordure) :** Stratégie déterministe réduisant le nombre de coups, mais plus lente car elle scanne la bordure à chaque tour.
* **Algorithme 4 (Max-Bordure-Zone) :** Amélioration du précédent. Elle privilégie les couleurs ouvrant de grandes zones connectées, offrant un score systématiquement meilleur.
* **Algorithme 5 (Estimation) :** Simule l'inondation via un marqueur virtuel (`VISITE_SIMU=-9`). C'est la stratégie la plus optimale en termes de nombre de coups.

## Installation et Compilation
Clonez le dépôt sur votre machine locale :

```bash
git clone [https://github.com/Aimenkhimoum/Flood-It-C.git](https://github.com/Aimenkhimoum/Flood-It-C.git)
cd Flood-It-C
```
Utilisez le Makefile fourni pour gérer la compilation :

Tout compiler : make

Jeu seul : make FloodIt

Tests de performance : make Test_Temps Test_Strategies comp_exo2_exo3

## Exécution du jeu
Pour lancer une partie, utilisez la syntaxe suivante :
```bash
./Flood-It <dim> <nbcl> <difficulte> <graine> <algo> <aff>
```

Exemple : 
```bash 
./FloodIt 500 10 2 20 3 1
```
Taille 500x500, 10 couleurs, difficulté 2, graine 20, Algo Max-Bordure, Affichage activé

Codes des Algorithmes :
Récursif

Rapide (Itératif)

Max-Bordure

Max-Bordure-Zone

Estimation

## Génération des courbes de performance
Pour reproduire les analyses comparatives présentes dans le rapport :

Exécuter les scripts de test :

```bash
./Test_Temps
./comp_exo2_exo3
./Test_Strategies
```

Lancer les scripts Gnuplot :

```bash
gnuplot courbes.gp
gnuplot comparaison2.gp
gnuplot plot_strategies.gp
```
Les images .png seront automatiquement générées dans le dossier du projet.

## Difficultés rencontrées
Gestion de la mémoire : Une rigueur particulière a été nécessaire pour éviter les fuites de mémoire (free) lors de la manipulation fréquente des listes chaînées et des bordures.

Modularité : Conception d'un Makefile capable de gérer plusieurs exécutables de tests simultanément.
