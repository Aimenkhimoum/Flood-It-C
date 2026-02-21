#include "Entete_Fonctions.h"
#include <stdio.h>
#include <stdlib.h>

/* Q 1.1 : trouver une zone récursivement */
void trouve_zone_rec(int **M, int dim, int i, int j, int *taille, ListeCase *L) {
    // sauvegarder la couleur avec i et j entrés
    int couleur_courante = M[i][j]; 

    //  ajouter la case(i,j) à la liste et augmenter la taille de la zone
    ajoute_en_tete(L, i, j);
    (*taille)++;

    // marquer la case comme visitée pour ne pas la parcourir encore une fois
    M[i][j] = -1;

    // appels récursifs sur les voisins haut ,bas, gauche et droite
    
    // voisin bas (i+1, j)
    if (i+1 <dim && M[i+1][j] == couleur_courante) { //si la case est dans la grille et de couleur == couleur_courante
        trouve_zone_rec(M, dim, i + 1, j, taille, L);
    }
    // voisin haut (i-1, j)
    if (i- 1 >= 0 && M[i-1][j] == couleur_courante) { //si la case est dans la grille et de couleur == couleur_courante
        trouve_zone_rec(M, dim, i - 1, j, taille, L);
    }
    // voisin droite (i, j+1)
    if (j+ 1 < dim && M[i][j+1] == couleur_courante) { //si la case est dans la grille et de couleur == couleur_courante
        trouve_zone_rec(M, dim, i, j + 1, taille, L);
    }
    // voisin gauche (i, j-1)
    if (j-1 >= 0 && M[i][j-1] == couleur_courante) { // si la case est dans la grille et de couleur == couleur_courante
        trouve_zone_rec(M, dim, i, j - 1, taille, L);
    }
}

/* Q 1.2 : sequence de jeu aleatoire en utilisant la fonction recursive pour trouver la Zsg*/
int sequence_aleatoire_rec(int **M, Grille *G, int dim, int nbcl, int aff) {
    int cpt = 0;        // variable pour compter le nombre de coups joués
    int taille = 0;     // taille de la Zsg initiale
    ListeCase L = NULL; // liste des cases de la Zsg pour l'utiliser dans trouve_zone_rec
    int ancienne_couleur;  //variable pour sauveagarder la couleur actuelle de la Zsg
    int nouvelle_couleur;  //variable pour la nouvelle couleur aléatoirement choisie
    
    
    // on boucle tant que la grille n'est pas totalement remplie
    while(taille < dim*dim) {
        
        // initialiser la taille de la liste et L 
        taille = 0;
        init_liste(&L);
        
        ancienne_couleur = M[0][0]; // on commence toujours la boucle avec la couleur de la case(0,0) qui represente la couleur de la Zsg

        // trouver la zone connécté à (0,0) (trouver la Zsg)
        trouve_zone_rec(M, dim, 0, 0, &taille, &L); //maintenant la liste L contient toutes les cases de la Zsg et taille est la taille de la Zsg

        // si toute la grille est remplie, la partie est finie
        if (taille == dim*dim) {
            detruit_liste(&L); //on libere la liste et on quitte la fonction
            break;
        }

        // choix d'une nouvelle couleur aléatoire différente de l'ancienne couleur
        do {
            nouvelle_couleur = rand()%nbcl;
        } while(nouvelle_couleur == ancienne_couleur);

        cpt++; // on compte un coup joué

        
        ListeCase temp = L; // temp pour parcourir la liste sans la perdre
        while(!test_liste_vide(&temp)) {  //si la liste est vide donc on a recolorié toute la Zsg 
            
            int i, j;
            enleve_en_tete(&L, &i, &j); // on dépile la dérnière case rajoutée à L 
            
            M[i][j] = nouvelle_couleur; // on applique la nouvelle couleur
            
            if(aff == 1) { // si aff = 1 on met à jour l'affichage
                Grille_attribue_couleur_case(G, i, j, nouvelle_couleur);
            }
            
            //on met a jour L pour pointer sur le prochain élément
            temp = L; 
           }

        if(aff==1) { 
            Grille_redessine_Grille(G); // on redessine la grille si aff = 1
        }
    }

    return cpt; // on retourne le nombre de coups total
}