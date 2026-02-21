#ifndef __S_ZSG_H__
#define __S_ZSG_H__
#include "API_Grille.h"
#include "Liste_case.h" 

// constantes pour le tableau App
#define NON_RENCONTRE -2 // case ni dans Zsg, ni dans la Bordure
#define DANS_ZSG      -1 // case dans la Zone Zsg

/* structure S_Zsg */
typedef struct {
    int dim;          /* dimension de la grille */
    int nbcl;         /* nombre de couleurs */
    
    ListeCase Lzsg;   /* Liste des cases de la zone Zsg */
    ListeCase *B;     /* Tableau de listes de cases de la bordure (taille nbcl) */
    int **App;        /* Tableau à double entrée des appartenances (dim x dim) */
    
} S_Zsg;

// prototypes des fonctions (Q 2.1)

/* initialise la structure S_Zsg*/
S_Zsg *init_Zsg(int dim, int nbcl);

/* ajoute une case (i, j) dans la liste Lzsg. complexité O(1)*/
void ajoute_Zsg(S_Zsg *S, int i, int j);

/* ajoute une case (i, j) dans la bordure de couleur cl donnée (B[cl]). complexité O(1)*/
void ajoute_Bordure(S_Zsg *S, int i, int j, int cl);

/* renvoie 1 si la case (i, j) est dans Lzsg, 0 sinon. complexité O(1) */
int appartient_Zsg(S_Zsg *S, int i, int j);

/* renvoie 1 si la case (i, j) est dans la bordure de couleur cl donnée, 0 sinon. complexité O(1) */
int appartient_Bordure(S_Zsg *S, int i, int j, int cl);

/* fonction de libération mémoire */
void detruit_Zsg(S_Zsg *S);

/* Q 2.2 agrandit la zone Zsg à partir de la case (k, l) de couleur cl */
int agrandit_Zsg(int **M, S_Zsg *Z, int cl, int k, int l);

/* Q 2.3 sequence_aleatoire_rapide */
int sequence_aleatoire_rapide(int **M, Grille *G, int dim, int nbcl, int aff);

/* Q 3.1 Compte le nombre de cases dans la bordure de couleur cl */
int nombre_cases_bordure(S_Zsg *Z, int cl); 
#endif

