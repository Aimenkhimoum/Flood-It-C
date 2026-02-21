#ifndef __ENTETE_FONCTIONS__
#define __ENTETE_FONCTIONS__

#include "API_Grille.h"
#include "Liste_case.h"
#include "S_Zsg.h"

/*  Structures pour l'exo 4  */

// noeud qui contient une liste de cases formant une zone connexe
typedef struct Zone_node {
    ListeCase zone;         // liste des coordonnées (i,j) de cette zone
    struct Zone_node *suiv; // pointeur vers la zone suivante (liste chainée)
} Zone_node;

//la structure principale inspirée de S_Zsg de l'exo 2 mais adaptée pour gérer les zones
typedef struct {
    int dim;                // dimension de la grille
    int nbcl;               // nombre de couleurs

    ListeCase Lzsg;         // liste des cases de la Zone 
    Zone_node **BZ;         // tableau de listes de zones (Bordure Zones)
                            // BZ[c] contient toutes les cases de couleur 'c' adjacentes à Zsg
    
    int *taille_BZ;         //  taille_BZ[c] = nombre total de cases gagnées si on joue 'c'
    int **App;              // matrice d'appartenance pour éviter les doublons :
                            // -1 si appartient à Zsg
                            // -2 si Inconnu (pas encore visité)
                            // 0..C-1 si ppartient à une zone de bordure déjà identifiée
} S_zsg_zone;

/* --- Prototypes --- */

/*pour l'exo 4*/
void init_Zsg_zone(S_zsg_zone *Z, int dim, int nbcl); // initialise la structure Zsg_zone

void desalloue_Zsg_zone(S_zsg_zone *Z); // desalloue la structure Zsg_zone

int agrandit_Zsg_zone(int **M, S_zsg_zone *Z, int cl); // agrandit la Zsg en jouant la couleur cl

/*Q 1.1 : fonction récursive pour trouver la Zsg */
void trouve_zone_rec(int **M, int dim, int i, int j, int *taille, ListeCase *L);

/*Q 1.2 : séquence aléatoire récursive */
int sequence_aleatoire_rec(int **M, Grille *G, int dim, int nbcl, int aff);

/*EXO3 : stratégie max bordure en choisissant la meilleure couleur */
int strategie_max_bordure(int **M, Grille *G, int dim, int nbcl, int aff);

/*EXO4 : stratégie max bordure en choisissant la meilleure couleur qui a la plus grande taille de la zone */
int strategie_max_bordure_zone(int **M, Grille *G, int dim, int nbcl, int aff);

/*EXO5 : stratégie proposée qui simule chaque couleur et prend la meilleure */
int strategie_exo5(int **M, Grille *G, int dim, int nbcl, int aff);

#endif