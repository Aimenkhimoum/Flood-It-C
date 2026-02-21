#include <stdio.h>
#include <stdlib.h>
#include "Entete_Fonctions.h"
#include "API_Grille.h" 


// ajoute une case en tête d'une liste 
void ajoute_en_tete_local(ListeCase *L, int i, int j) {
    ListeCase nouv = (ListeCase)malloc(sizeof(Elnt_liste));
    nouv->i = i;
    nouv->j = j;
    nouv->suiv = *L;
    *L = nouv;
}

// récursivité pour trouver tous les pixels d'une même tache de couleur , inspirée de trouve_zone_rec mais avec App en plus
void trouve_zone_rec_local(int **M, int dim, int i, int j, int *taille, ListeCase *L, int **App) {
    int cl = M[i][j];
    
    // ajout du pixel courant
    ajoute_en_tete_local(L, i, j);
    (*taille)++;
    App[i][j] = cl; // marqué comme appartenant à une zone de bordure de couleur cl

    int di[] = {0, 0, 1, -1}; //tableaux des déplacements
    int dj[] = {1, -1, 0, 0};

    //boucle pour explorer les 4 voisins
    for (int k = 0; k < 4; k++) {
        int ni = i + di[k];
        int nj = j + dj[k];

        // vérification des limites de la grille
        if (ni >= 0 && ni < dim && nj >= 0 && nj < dim) {
            
             // si même couleur et (jamais visité (-2) )
              if (M[ni][nj] == cl && App[ni][nj] == -2) {
                trouve_zone_rec_local(M, dim, ni, nj, taille, L, App);
            }
        }
    }
}

// ajoute une zone entière découverte dans la structure BZ
void ajoute_zone_bordure(S_zsg_zone *Z, int cl, ListeCase ma_zone, int taille_ajout) {
    Zone_node *new_node = (Zone_node *)malloc(sizeof(Zone_node));
    new_node->zone = ma_zone;
    new_node->suiv = Z->BZ[cl];
    Z->BZ[cl] = new_node;

    Z->taille_BZ[cl] += taille_ajout; // mise à jour du score obtenu avec cette couleur
}

//une fonction pour initialiser la structure Zsg_zone
void init_Zsg_zone(S_zsg_zone *Z, int dim, int nbcl) {
    Z->dim = dim;
    Z->nbcl = nbcl;
    Z->Lzsg = NULL;
    Z->BZ = (Zone_node **)malloc(nbcl * sizeof(Zone_node*));
    Z->taille_BZ = (int *)calloc(nbcl, sizeof(int)); // init à 0
    Z->App = (int **)malloc(dim * sizeof(int*));

    for (int c = 0; c < nbcl; c++) Z->BZ[c] = NULL;

    for (int i = 0; i < dim; i++) {
        Z->App[i] = (int *)malloc(dim * sizeof(int));
        for (int j = 0; j < dim; j++) {
            Z->App[i][j] = -2; // -2  Inconnu
        }
    }
}


void desalloue_Zsg_zone(S_zsg_zone *Z) {
    // libérer Zsg
    detruit_liste(&(Z->Lzsg)); 

    // iibérer BZ
    for (int c = 0; c < Z->nbcl; c++) {
        Zone_node *cour = Z->BZ[c];
        while (cour != NULL) {
            Zone_node *tmp = cour;
            detruit_liste(&(cour->zone));
            cour = cour->suiv;
            free(tmp);
        }
    }
    free(Z->BZ);
    free(Z->taille_BZ);

    // libérer App
    for (int i = 0; i < Z->dim; i++) free(Z->App[i]);
    free(Z->App);
}

// on met à jour Zsg, App, et découvre les nouvelles zones 
int agrandit_Zsg_zone(int **M, S_zsg_zone *Z, int cl) {
    int nb_ajoute = 0;  // nombre de cases ajoutées à la Zsg
    int di[] = {0, 0, 1, -1};  //tableaux des déplacements
    int dj[] = {1, -1, 0, 0};

    // 
    // on récupère toutes les zones stockées dans BZ[cl]
    Zone_node *zone_cour = Z->BZ[cl];
    ListeCase cases_a_explorer = NULL; 

    while (zone_cour != NULL) {
        ListeCase case_cour = zone_cour->zone;
        while (case_cour != NULL) {
            int i = case_cour->i;
            int j = case_cour->j;

            // ajout à Zsg
            ajoute_en_tete_local(&(Z->Lzsg), i, j);
            Z->App[i][j] = -1; // on marque dans Zsg
            nb_ajoute++;
            
            // on sauvegarde la case pour explorer les voisins après
            ajoute_en_tete_local(&cases_a_explorer, i, j);

            case_cour = case_cour->suiv;
        }
        zone_cour = zone_cour->suiv;
    }

    //nettoyage de la liste BZ[cl]
    zone_cour = Z->BZ[cl];
    while (zone_cour != NULL) {
        Zone_node *temp = zone_cour;
        detruit_liste(&(temp->zone));
        zone_cour = zone_cour->suiv;
        free(temp);
    }
    Z->BZ[cl] = NULL;
    Z->taille_BZ[cl] = 0; 

    
    // on regarde les voisins des cases qu'on vient d'ajouter pour les explorer
    ListeCase case_ajoutee = cases_a_explorer;
    while (case_ajoutee != NULL) {
        int i = case_ajoutee->i;
        int j = case_ajoutee->j;

        for (int k = 0; k < 4; k++) {
            int ni = i + di[k];
            int nj = j + dj[k];

            if (ni >= 0 && ni < Z->dim && nj >= 0 && nj < Z->dim) {
                // si la case est INCONNUE (-2)
                if (Z->App[ni][nj] == -2) {
                    int taille_zone = 0;
                    ListeCase nouvelle_zone = NULL;
                    
                    // on lance l'inondation pour trouver toute la tache connectée
                    trouve_zone_rec_local(M, Z->dim, ni, nj, &taille_zone, &nouvelle_zone, Z->App);

                    int coul_voisin = M[ni][nj];
                    ajoute_zone_bordure(Z, coul_voisin, nouvelle_zone, taille_zone);
                }
            }
        }
        case_ajoutee = case_ajoutee->suiv;
    }

    detruit_liste(&cases_a_explorer);
    return nb_ajoute;
}

// fonction on va l'utiliser dans le main
int strategie_max_bordure_zone(int **M, Grille *G, int dim, int nbcl, int aff) {
    S_zsg_zone Z;
    int nb_changements = 0;
    
    // initialisation de la structure
    init_Zsg_zone(&Z, dim, nbcl);

    // on commence toujours par ajouter la case (0,0) à la Zsg et découvrir ses voisins
    ListeCase debut = NULL;
    ajoute_en_tete_local(&debut, 0, 0);
    Z.App[0][0] = -2; // pour que la fonction agrandit_zone_rec l'accepte on doit modifier à -2
    
    //on commence par ajouter la zone (0,0)
    ajoute_zone_bordure(&Z, M[0][0], debut, 1);
    
    // on absorbe (0,0) et on découvre ses voisins
    agrandit_Zsg_zone(M, &Z, M[0][0]); 

    //boucle du jeu
    // meme logique utilisé préceedemment , tant que taille est inférieure à la taille totale
    int taille_totale = 1; // on a deja (0,0)
    while(taille_totale < dim*dim) {
        
        int meilleur_cl = -1; //meme logique que dans l'exo 3
        int max_gain = -1;

        for (int c = 0; c <nbcl; c++) {
            
            if (Z.taille_BZ[c] > max_gain) {
                max_gain = Z.taille_BZ[c];
                meilleur_cl = c;
            }
        }


        // on joue la meilleure couleur trouvée
        taille_totale += agrandit_Zsg_zone(M, &Z, meilleur_cl);
        nb_changements++;

        //meme logique utilisé pour l'affichage précedemment 
        ListeCase p = Z.Lzsg;
        while(p != NULL){
            M[p->i][p->j] = meilleur_cl;
            if (aff==1){ 
                Grille_attribue_couleur_case(G, p->i, p->j, meilleur_cl);}
            p = p->suiv;
        }
        if (aff==1){

        Grille_redessine_Grille(G);
    }
}

    desalloue_Zsg_zone(&Z);
    return nb_changements;
}