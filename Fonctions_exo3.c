#include <stdio.h>
#include <stdlib.h>
#include "Entete_Fonctions.h"
#include "S_Zsg.h"

// Exo 3 : Q 3.1 : compte le nombre de cases dans la bordure de couleur cl d'une Zsg Z
 int nombre_cases_bordure(S_Zsg *Z, int cl){
    int count = 0; // compteur de cases 
    ListeCase p = Z->B[cl];   //liste des cases de la bordure de couleur cl 
    while(p != NULL) {
        count++;
        p = p->suiv;
    }
    return count; //on retourne le nombre de cases de la bordure cl 
}


/* exo 3 Stratégie Max-Bordure qui aggrandit la zone en fonction de la meilleure taille de la bordure */
int strategie_max_bordure(int **M, Grille *G, int dim, int nbcl, int aff) {
    int cpt = 0; // compteur de coups
    int cur_color = M[0][0]; //couleur courante initiale 
    int taille = 0; // taille initiale de la Zsg
    int best_color; // variable pour la meilleure couleur
    int max_bordure; // variable pour la taille maximale de la bordure
    
    // initialisation de la structure
    S_Zsg *Z = init_Zsg(dim, nbcl);
    
    // initialisation de la zone de départ avec la case (0,0)
    taille = agrandit_Zsg(M, Z, cur_color, 0, 0);

    //  boucle du jeu tant que la taille de la Zsg est inférieure à la taille totale de la grille
    while(taille < dim*dim) {
        cpt++; // on incremente le nombre de coups
        
        // on cherche la couleur qui a le plus grand nombre de cases en bordure 
        max_bordure = -1;    //initialisation de la taille maximale de la bordure
        best_color = -1;     //initialisation de la meilleure couleur

        for (int c = 0; c < nbcl;c++) {
            // on ne peut pas jouer la couleur actuelle car elle n'est pas en bordure
            if (c == cur_color) continue; // on saute la couleur courante

            // en utilisant la fonction de la Q 3.1 : on compte la taille de la bordure pour la couleur c
            int nb = nombre_cases_bordure(Z, c);
            
            // si le nombre de cette couleur est plus grande que max_bordure, on la garde
            if (nb > max_bordure) {
                max_bordure = nb;   //on met à jour la taille maximale de la bordure
                best_color = c;     // on met à jour la nouvelle meilleure couleur
            }
        }


        // on joue la meilleure couleur trouvée
        cur_color = best_color;

        // on met à jour de la grille (couleur de la zone)
        ListeCase temp = Z->Lzsg;   //meme parcours de la liste utilisé dans l'exo 2

        while(temp != NULL) {

            M[temp->i][temp->j] = cur_color;
            if(aff == 1) Grille_attribue_couleur_case(G, temp->i, temp->j, cur_color);
            temp = temp->suiv;
        }

        // agrandissement de la zone avec les cases de la bordure gagnante
        ListeCase p = Z->B[cur_color];
        while(p != NULL) {
            taille += agrandit_Zsg(M, Z, cur_color, p->i, p->j); //on incremente la taille de la Zsg
            p = p->suiv;
        }
        
        // on detruit la liste bordure de la couleur jouée car ce n'est plus une bordure
        detruit_liste(&(Z->B[cur_color]));

        // affichage si aff =1
        if(aff == 1) Grille_redessine_Grille(G);
    }

    detruit_Zsg(Z);
    return cpt;  //on retourne le nombre de coups total 
}